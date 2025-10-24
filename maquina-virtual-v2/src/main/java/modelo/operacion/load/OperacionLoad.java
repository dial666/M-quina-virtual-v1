/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.load;

import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operacion.IOperacion;
import modelo.operando.Operando;
import modelo.operando.OperandoMemoria;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public abstract class OperacionLoad implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        int valorA = opA.getValor(mv);
        int valorB = opB.getValor(mv);
        boolean fourBytes;
        
        if (opA instanceof OperandoMemoria)
            fourBytes = ((OperandoMemoria) opA).getCodTamanioCelda() == 0;
        else
            fourBytes = opA instanceof OperandoRegistroE;
        
        int resultado = (fourBytes)? cuenta(valorA, valorB): valorB;
        opA.setValor(mv, resultado);
    }
    
    public abstract int cuenta(int valorA, int valorB);
}
