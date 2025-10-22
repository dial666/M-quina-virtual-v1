/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import modelo.Contexto;
import modelo.excepciones.SegmentationFaultException;

/**
 *
 * @author valen
 */
public class OperandoInmediato implements Operando
{
    private int valor;
    
    public OperandoInmediato(int operandoInmediato)
    {
        this.valor = operandoInmediato;
    }

    public int getValor()
    {
        return valor;
    }

    @Override
    public String toString()
    {
        return "" + this.valor;
    }

    @Override
    public int getValor(Contexto vmx)
    {
        int val = 0;
        try
        {
            val = vmx.getValor(this);
        } 
        catch (SegmentationFaultException e)
        {
            throw new IllegalStateException("no deberia ocurrir un segmentation fault en un inmediato");
        }
        return val;
    }

    @Override
    public int setValor(Contexto Vmx) throws SegmentationFaultException, IllegalArgumentException
    {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }
    
}
