/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operando.Operando;

/**
 *
 * @author valen
 */
public class Mov implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        opA.setValor(mv, opB.getValor(mv));
    }

    @Override
    public String toString()
    {
        return "MOV";
    }

}
