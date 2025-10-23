/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo.inicio;

import java.nio.ByteBuffer;
import modelo.Memoria;
import modelo.Registros;
import modelo.TablaSegmentos;
import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public interface IInicializadorMV
{
    public void inicializa(Memoria memoria, Registros registro, TablaSegmentos tablaSegmentos, String[] params, ByteBuffer byteBufferArch) throws VMException;
}
