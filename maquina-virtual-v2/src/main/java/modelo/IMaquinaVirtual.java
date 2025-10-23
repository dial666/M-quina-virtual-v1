/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo;

import java.io.FileNotFoundException;
import java.io.IOException;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.VMException;
import modelo.operando.Operando;
import modelo.operando.OperandoInmediato;
import modelo.operando.OperandoMemoria;
import modelo.operando.OperandoRegistro;

/**
 *
 * @author valen
 */
public interface IMaquinaVirtual
{
    public void ejecutar() throws VMException;
    public void creaImagen() throws VMException, FileNotFoundException, IOException;
}
