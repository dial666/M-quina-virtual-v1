/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.nio.ByteBuffer;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.TablaSegmentosLlenaException;
import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public class TablaSegmentos
{
    private static int cantEntradas = 8;
    private int[] tablaSegmentos;
    
    public TablaSegmentos()
    {
        this.tablaSegmentos = new int[TablaSegmentos.getCantEntradas()];
        
        for (int i = 0; i < TablaSegmentos.getCantEntradas(); i++) 
        {
            this.tablaSegmentos[i] = -1;
        }   
    }
    
    public int getDirFisica(int dirLogica, int cantBytes) throws SegmentationFaultException
    {
        int indiceTabla = IntUtils.getHighSigned(dirLogica);
        int offset = IntUtils.getLowSigned(dirLogica);
        
        if (indiceTabla < 0 || indiceTabla >= TablaSegmentos.getCantEntradas() || this.tablaSegmentos[indiceTabla] == -1)
            throw new SegmentationFaultException("segmentation fault");
        
        int dirBase = IntUtils.getHighUnsigned(this.tablaSegmentos[indiceTabla]);
        int dirFisica = dirBase + offset;
        int tamSegmento = IntUtils.getLowUnsigned(this.tablaSegmentos[indiceTabla]);
        if (dirBase <= dirFisica && dirBase + tamSegmento >= dirFisica + cantBytes)
            return dirFisica;
        else
            throw new SegmentationFaultException("segmentation fault"); 
    }
    
    /**
     * 
     * @param tamSegmento
     * @return indice de la entrada en la tabla de segmentos
     * @throws TablaSegmentosLlenaException 
     */
    public int agregarEntrada(int tamSegmento) throws  TablaSegmentosLlenaException
    {
        int i = 0;
        int n = TablaSegmentos.getCantEntradas();
        while (i < n && this.tablaSegmentos[i] != -1)
            i++;
        
        if (i >= n)
            throw new TablaSegmentosLlenaException("la tabla de segmentos no tiene espacio para mas segmentos");
        
        int base;
        if (i > 0)
            base = IntUtils.getHighUnsigned(this.tablaSegmentos[i-1]) + IntUtils.getLowUnsigned(this.tablaSegmentos[i-1]);
        else
            base = 0;
        
         this.tablaSegmentos[i] = IntUtils.putHigh(0, base);
         this.tablaSegmentos[i] = IntUtils.putLow(this.tablaSegmentos[i], tamSegmento);
         return i;
    }

    public static int getCantEntradas()
    {
        return cantEntradas;
    }

    public static void setCentEntradas(int centEntradas)
    {
        TablaSegmentos.cantEntradas = centEntradas;
    }

    public int[] getTablaSegmentos()
    {
        return tablaSegmentos;
    }    
    
    public byte[] getBytes()
    {
        ByteBuffer byteBuffer = ByteBuffer.allocate(this.tablaSegmentos.length * Integer.BYTES);
        for (int valor: this.tablaSegmentos)
            byteBuffer.putInt(valor);
        return byteBuffer.array();
    }

    public void setTablaSegmentos(int[] tablaSegmentos)
    {
        this.tablaSegmentos = tablaSegmentos;
    }
}
