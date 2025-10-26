/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.inicio;

import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import modelo.Memoria;
import modelo.Registros;
import modelo.TablaSegmentos;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.StackOverflowException;
import modelo.excepciones.VMException;
import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public class InicializadorMV2 implements IInicializadorMV
{

    @Override
    public void inicializa(Memoria memoria, Registros registros, TablaSegmentos tablaSegmentos, String[] params, ByteBuffer byteBufferArch) throws VMException
    {
        int tamCS = byteBufferArch.getShort() & 0xFFFF;
        int tamDS = byteBufferArch.getShort() & 0xFFFF;
        int tamES = byteBufferArch.getShort() & 0xFFFF;
        int tamSS = byteBufferArch.getShort() & 0xFFFF;
        int tamKS = byteBufferArch.getShort() & 0xFFFF;
        int tamPS = tamanioParams(params) + params.length*4;
        int indice;
        int dirFisica;
        int entryPoint;
        int punteroPunteros;
        
        if (tamCS+tamDS+tamES+tamSS+tamKS+tamPS > memoria.getTamanio())
            throw new VMException("el tamanio de los segmentos supera el tamanio de la memoria");
        
        entryPoint = byteBufferArch.getShort() & 0xFFFF;
        
        byteBufferArch.position(12);
        byteBufferArch = byteBufferArch.slice();
        
        if (tamPS > 0)
        {
            indice = tablaSegmentos.agregarEntrada(tamPS);
            registros.setPS(IntUtils.putHigh(0, indice));
            System.out.println("" + registros.getPS());
            dirFisica = tablaSegmentos.getDirFisica(registros.getPS(), tamPS);
            memoria.setBloque(dirFisica, bytesParams(params, registros.getPS()));
            punteroPunteros = registros.getPS() + tamanioParams(params);
        }
        else
        {
            registros.setPS(-1);
            punteroPunteros = -1;
        }
        
        if (tamKS > 0)
        {
            indice = tablaSegmentos.agregarEntrada(tamKS);
            registros.setKS(IntUtils.putHigh(0, indice));
              
            ByteBuffer constantesBuffer = byteBufferArch.slice(tamCS, tamKS);
            byte[] constantes = new byte[tamKS];
            constantesBuffer.get(constantes);
            
            dirFisica = tablaSegmentos.getDirFisica(registros.getKS(), tamKS);
            memoria.setBloque(dirFisica, constantes);
        }
        else
            registros.setKS(-1);
          
        if (tamCS > 0)
        {
            indice = tablaSegmentos.agregarEntrada(tamCS);
            registros.setCS(IntUtils.putHigh(0, indice));
            
            ByteBuffer codigoBuffer = byteBufferArch.slice(0, tamCS);
            byte[] codigo = new byte[tamCS];
            codigoBuffer.get(codigo);
            
            dirFisica = tablaSegmentos.getDirFisica(registros.getCS(), tamCS);
            memoria.setBloque(dirFisica, codigo);
        }
        else
            registros.setCS(-1);
        
        if (tamDS > 0)
        {
            indice = tablaSegmentos.agregarEntrada(tamDS);
            registros.setDS(IntUtils.putHigh(0, indice));
        }
        else
            registros.setDS(-1);
        
        if (tamES > 0)
        {
            indice = tablaSegmentos.agregarEntrada(tamES);
            registros.setES(IntUtils.putHigh(0, indice));
        }
        else
            registros.setES(-1);
        
        if (tamSS > 0)
        {
            indice = tablaSegmentos.agregarEntrada(tamSS);
            registros.setSS(IntUtils.putHigh(0, indice));
        }
        else
            registros.setSS(-1);
        
        registros.setIP(registros.getCS() + entryPoint);
        registros.setSP(registros.getSS() + tamSS);
        
        try
        {
            registros.setSP(registros.getSP()-4);
            dirFisica = tablaSegmentos.getDirFisica(registros.getSP(), 4);
            memoria.setValor(dirFisica, 4, punteroPunteros);

            registros.setSP(registros.getSP()-4);
            dirFisica = tablaSegmentos.getDirFisica(registros.getSP(), 4);
            memoria.setValor(dirFisica, 4, params.length);

            registros.setSP(registros.getSP()-4);
            dirFisica = tablaSegmentos.getDirFisica(registros.getSP(), 4);
            memoria.setValor(dirFisica, 4, -1);
        } catch (SegmentationFaultException e)
        {
           throw new StackOverflowException("stack overflow");
        }
    }

    
    
    protected int tamanioParams(String[] params)
    {
        int cont = 0;
        for (String param: params)
            cont += param.length();
        cont += params.length;
        return cont;
    }
    
    protected byte[] bytesParams(String[] params, int registroPS)
    {     
        ByteBuffer paramsBytes = ByteBuffer.allocate(tamanioParams(params) + params.length *4);
        int[] punterosParams = new int[params.length];
        int offset = 0;
        for (int i = 0; i < params.length; i++)
        {
            punterosParams[i] = registroPS + offset;
            paramsBytes.put(params[i].getBytes(StandardCharsets.US_ASCII));
            paramsBytes.put((byte) 0);
            offset += params[i].length() + 1;
        }
        
        for (int puntero: punterosParams)
            paramsBytes.putInt(puntero);
        
        return paramsBytes.array();
    }
    
}
