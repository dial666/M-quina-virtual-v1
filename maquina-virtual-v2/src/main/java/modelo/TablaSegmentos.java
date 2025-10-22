/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import modelo.excepciones.SegmentationFaultException;
import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public class TablaSegmentos
{
    private static int centEntradas = 8;
    private int[] tablaSegmentos;
    
    public TablaSegmentos()
    {
        this.tablaSegmentos = new int[TablaSegmentos.getCentEntradas()];
        
        for (int i = 0; i < TablaSegmentos.getCentEntradas(); i++) 
        {
            this.tablaSegmentos[i] = -1;
        }   
    }
    
    public int getDirFisica(int dirLogica, int cantBytes) throws SegmentationFaultException
    {
        int indiceTabla = IntUtils.getHigh(dirLogica);
        int offset = IntUtils.getLow(dirLogica);
        
        if (indiceTabla < 0 || indiceTabla >= TablaSegmentos.getCentEntradas() || this.tablaSegmentos[indiceTabla] == -1)
            throw new SegmentationFaultException("segmentation fault");
        
        int dirBase = IntUtils.getHigh(this.tablaSegmentos[indiceTabla]);
        int dirFisica = dirBase + offset;
        int tamSegmento = IntUtils.getLow(this.tablaSegmentos[indiceTabla]);
        if (dirBase <= dirFisica && dirBase + tamSegmento >= dirFisica + cantBytes)
            return dirFisica;
        else
            throw new SegmentationFaultException("segmentation fault");
        
    }

    public static int getCentEntradas()
    {
        return centEntradas;
    }

    public static void setCentEntradas(int centEntradas)
    {
        TablaSegmentos.centEntradas = centEntradas;
    }
            
    
}
