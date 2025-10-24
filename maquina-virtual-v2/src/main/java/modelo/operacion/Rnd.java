/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import java.util.Random;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operando.Operando;

/**
 *
 * @author valen
 */
public class Rnd implements IOperacion
{

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        Random r = new Random();
        opA.setValor(mv, r.nextInt(opB.getValor(mv)));
    }

    @Override
    public String toString()
    {
        return "RND";
    }
    
    
}
