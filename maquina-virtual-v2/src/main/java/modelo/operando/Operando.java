/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo.operando;

import modelo.excepciones.SegmentationFaultException;
import modelo.UnidadIO;

/**
 *
 * @author valen
 */
public interface Operando
{
    public int getValor(UnidadIO vmx) throws SegmentationFaultException;
    public void setValor(UnidadIO vmx, int valor) throws SegmentationFaultException;
}
