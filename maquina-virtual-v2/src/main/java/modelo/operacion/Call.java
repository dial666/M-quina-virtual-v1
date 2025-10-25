/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operacion.jump.Jmp;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public class Call implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        IOperacion operacionPush = new Push();
        IOperacion operacionJmp = new Jmp();
        operacionPush.ejecutar(new OperandoRegistroE(ConstantesRegistros.IP.getCodigo()), opB, mv);
        operacionJmp.ejecutar(opA, opB, mv);
    }

    @Override
    public String toString()
    {
        return "CALL";
    }
}
