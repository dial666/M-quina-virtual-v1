/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public class Stop implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        Operando opIP = new OperandoRegistroE(ConstantesRegistros.IP.getCodigo());
        opIP.setValor(mv, -1);
    }

    @Override
    public String toString()
    {
        return "STOP";
    }
    
    
}
