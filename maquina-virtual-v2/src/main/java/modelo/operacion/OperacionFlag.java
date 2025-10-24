/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.ConstantesRegistros;
import modelo.Registros;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public class OperacionFlag implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {   
        int resultado = opB.getValor(mv);
        opA.setValor(mv, opA.getValor(mv) & 0x3FFFFFFF);
        if (resultado == 0)
            opA.setValor(mv, opA.getValor(mv) | 0x40000000);
        else
            if (resultado < 0)
                opA.setValor(mv, opA.getValor(mv) | 0x80000000);
    }
    
}
