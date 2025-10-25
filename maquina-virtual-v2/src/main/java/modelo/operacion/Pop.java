/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.StackUnderflowException;
import modelo.excepciones.VMException;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public class Pop implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        Operando opSP = new OperandoRegistroE(ConstantesRegistros.SP.getCodigo());
        int valorSP = opSP.getValor(mv);
        int valorPila = 0;
        try
        {
            valorPila = mv.getValorMemoriaModificaReg(valorSP, 4);
        } 
        catch (SegmentationFaultException e)
        {
            throw new StackUnderflowException("stack underflow");
        }
        opA.setValor(mv, valorPila);
        opSP.setValor(mv, valorSP + 4);
    }

    @Override
    public String toString()
    {
        return "POP";
    }   
}
