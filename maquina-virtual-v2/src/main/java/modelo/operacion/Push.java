/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.StackOverflowException;
import modelo.excepciones.StackUnderflowException;
import modelo.excepciones.VMException;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public class Push implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        Operando opSP = new OperandoRegistroE(ConstantesRegistros.SP.getCodigo());
        opSP.setValor(mv, opSP.getValor(mv) - 4);
        
        int valorOpA = opA.getValor(mv);
        try
        {
            mv.setValorMemoriaModifReg(opSP.getValor(mv), 4, valorOpA);
        } 
        catch (SegmentationFaultException e)
        {
            throw new StackOverflowException("stack overflow");
        }
    }

    @Override
    public String toString()
    {
        return "PUSH";
    }

}
