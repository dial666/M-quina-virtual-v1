/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo;

import modelo.excepciones.SegmentationFaultException;
import modelo.operando.Operando;

/**
 *
 * @author valen
 */
public interface UnidadIO
{
    public int getValor(Operando operando) throws SegmentationFaultException;
    public int getValorMemoriaModificaReg(int dirLogica, int cantBytes) throws SegmentationFaultException;
    public void setValor(Operando operando, int valor) throws SegmentationFaultException;   
    public void setValorMemoriaModifReg(int dirLogica, int cantBytes, int valor) throws SegmentationFaultException;
}
