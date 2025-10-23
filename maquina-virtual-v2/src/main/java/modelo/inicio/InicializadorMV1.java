/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.inicio;

import java.nio.ByteBuffer;
import modelo.Memoria;
import modelo.Registros;
import modelo.TablaSegmentos;
import modelo.excepciones.VMException;
import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public class InicializadorMV1 implements IInicializadorMV
{

    @Override
    public void inicializa(Memoria memoria, Registros registros, TablaSegmentos tablaSegmentos, String[] params, ByteBuffer byteBufferArch) throws VMException
    {
        int tamMemoria = memoria.getTamanio();
        int tamCodigo = byteBufferArch.getShort() & 0xFFFF;
        int indice;
        int dirFisica;
        byte[] codigo;
        ByteBuffer byteBufferCod;
        
        if (tamCodigo > tamMemoria)
            throw  new VMException("el tamanio del codigo supera al tamanio de la memoria");
       
        indice = tablaSegmentos.agregarEntrada(tamCodigo);
        registros.setCS(IntUtils.putHigh(0, indice));
        indice = tablaSegmentos.agregarEntrada(tamMemoria-tamCodigo);
        registros.setDS(IntUtils.putHigh(0, indice));
        registros.setIP(registros.getCS());
        registros.setKS(-1);
        
        byteBufferArch.position(2);
        byteBufferCod = byteBufferArch.slice();
        codigo = new byte[byteBufferCod.remaining()];
        byteBufferCod.get(codigo);
        
        dirFisica = tablaSegmentos.getDirFisica(registros.getCS(), codigo.length);
        memoria.setBloque(dirFisica, codigo);
    } 
}
