/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo.operando;

import modelo.Contexto;
import modelo.MaquinaVirtual;
import modelo.excepciones.SegmentationFaultException;

/**
 *
 * @author valen
 */
public interface Operando
{
    public int getValor(Contexto vmx) throws SegmentationFaultException;
    public int setValor(Contexto vmx) throws SegmentationFaultException, IllegalArgumentException;
}
