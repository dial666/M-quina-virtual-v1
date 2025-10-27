/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public class CreadorVMI1 extends CreadorVMI
{

    public CreadorVMI1(String archVmi)
    {
        super(archVmi);
    }
    
    @Override
    public void creaImagen(byte[] memoria, byte[] registros, byte[] tablaSegmentos) throws VMException, FileNotFoundException, IOException
    {
        if (this.archVmi == null)
            throw new VMException("no se proporciono un archivo .vmi para crear la imagen");
        short tamMemoria = (short) (memoria.length / 1024);

        ByteBuffer byteBuffer = ByteBuffer.allocate(2);
        byteBuffer.putShort(tamMemoria);
        FileOutputStream arch = new FileOutputStream(this.archVmi);
        arch.write("VMI25".getBytes(StandardCharsets.US_ASCII));
        arch.write(new byte[]{1});
        arch.write(byteBuffer.array());
        arch.write(registros);
        arch.write(tablaSegmentos);
        arch.write(memoria);
        arch.close();
    }
}
