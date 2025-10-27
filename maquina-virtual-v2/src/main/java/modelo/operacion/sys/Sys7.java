/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys;

import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operacion.IOperacion;
import modelo.operando.Operando;

/**
 *
 * @author Matu
 */
public class Sys7 implements IOperacion{

    public Sys7() {
    }

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
    
}
