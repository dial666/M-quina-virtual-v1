/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operando.Operando;
import modelo.operando.OperandoInmediato;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public class Not implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        int resultado = ~opA.getValor(mv);
        opA.setValor(mv, resultado);
        IOperacion op = new OperacionFlag();
        op.ejecutar(new OperandoRegistroE(ConstantesRegistros.CC.getCodigo()), new OperandoInmediato(resultado), mv);
    }

    @Override
    public String toString()
    {
        return "NOT";
    }  
}
