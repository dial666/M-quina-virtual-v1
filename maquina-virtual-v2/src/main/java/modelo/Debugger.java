/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.io.IOException;
import java.util.Scanner;
import modelo.excepciones.QuitException;
import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public class Debugger
{
    public void ejecutar(IDebuggeable mv) throws VMException, IOException
    {
            
            mv.creaImagen();
            mv.setBreakpoint(false);
            Scanner scanner = mv.getScanner();                
            String input = scanner.nextLine();
            if (input.equals("g"))
                mv.setPasoAPaso(false);
            else
                if (input.equals(""))
                    mv.setPasoAPaso(true);
                else
                    if (input.equals("q"))
                        throw new QuitException("");
    }
}
