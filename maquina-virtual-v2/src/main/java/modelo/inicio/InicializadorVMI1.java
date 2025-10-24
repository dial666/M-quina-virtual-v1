/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.inicio;

import java.nio.ByteBuffer;
import modelo.ConstantesRegistros;
import modelo.Memoria;
import modelo.Registros;
import modelo.TablaSegmentos;
import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public class InicializadorVMI1 implements IInicializadorMV
{

    @Override
    public void inicializa(Memoria memoria, Registros registros, TablaSegmentos tablaSegmentos, String[] params, ByteBuffer byteBufferArch) throws VMException
    {
        int tamMemoria;
        int tamRegistros = ConstantesRegistros.getCantidadRegistros() * Integer.BYTES;
        int tamTabla = TablaSegmentos.getCantEntradas() * Integer.BYTES;
        ByteBuffer bufferRegistros;
        ByteBuffer bufferTabla;
        ByteBuffer bufferMem;
        int[] arrayRegistros;
        int[] arrayTabla;
        byte[] arrayMemoria;
        int i;
        
        tamMemoria = byteBufferArch.getShort() & 0xFFFF;
        if (tamMemoria > memoria.getTamanio())
            throw new VMException("el tamanio de la memoria de la imagen supera el tamanio de la memoria de esta maquina");
        
        byteBufferArch = byteBufferArch.slice();
        bufferRegistros = byteBufferArch.slice(0, tamRegistros);
        bufferTabla = byteBufferArch.slice(tamRegistros, tamTabla);
        bufferMem = byteBufferArch.slice(tamRegistros + tamTabla, tamMemoria);
        
        arrayRegistros = new int[ConstantesRegistros.getCantidadRegistros()];
        for (i = 0; i < ConstantesRegistros.getCantidadRegistros(); i++)
            arrayRegistros[i] = bufferRegistros.getInt();
        registros.setRegistros(arrayRegistros);
        
        
        arrayTabla = new int[TablaSegmentos.getCantEntradas()];
        for (i = 0; i < TablaSegmentos.getCantEntradas(); i++)
            arrayTabla[i] = bufferTabla.getInt();
        tablaSegmentos.setTablaSegmentos(arrayTabla);
        
        arrayMemoria = new byte[tamMemoria];
        bufferMem.get(arrayMemoria);
        memoria.setBloque(0, arrayMemoria);
    }
    
}
