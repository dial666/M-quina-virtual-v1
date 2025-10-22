/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo;

import modelo.excepciones.SegmentationFaultException;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistro;

/**
 *
 * @author valen
 */
public interface Contexto
{
    public int getValor(Operando operando) throws SegmentationFaultException;
    public void setValor(Operando operando) throws SegmentationFaultException, IllegalArgumentException;   
}
