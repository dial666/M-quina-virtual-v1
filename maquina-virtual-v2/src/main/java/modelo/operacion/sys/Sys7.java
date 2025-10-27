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
        
        for(int i=0; i<50; i++)
            System.out.println();
        
        /*NADA FUNCIONO
        try {
            String os = System.getProperty("os.name");

            if (os.contains("Windows")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else {
                Runtime.getRuntime().exec("clear");
            }
        } catch (final Exception e) {
     
        }*/  
    }
    
}
