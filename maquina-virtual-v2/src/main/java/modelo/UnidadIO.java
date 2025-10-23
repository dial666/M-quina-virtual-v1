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
import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public interface UnidadIO
{
    public int getValor(Operando operando) throws SegmentationFaultException;
    public int getValor(OperandoInmediato operando);
    public int getValor(OperandoRegistro operando);
    public int getValor(OperandoMemoria operando) throws SegmentationFaultException;
    public int getValorMemoriaModificaReg(int dirLogica, int cantBytes) throws SegmentationFaultException;
    public int getValorMemoria(int dirLogica, int cantBytes) throws SegmentationFaultException;
    public void setValor(Operando operando, int valor) throws SegmentationFaultException;
    public void setValor(OperandoInmediato operando, int valor);
    public void setValor(OperandoRegistro operando, int valor);
    public void setValor(OperandoMemoria operando, int valor) throws SegmentationFaultException;
    public void setValorMemoriaModifReg(int dirLogica, int cantBytes, int valor) throws SegmentationFaultException;
    
    public void creaImagen() throws VMException, FileNotFoundException, IOException;
}
