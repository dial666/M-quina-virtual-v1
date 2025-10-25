/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public interface IDebuggeable
{
    public boolean isPasoAPaso();
    public boolean isAtenderDebugger();
    public void setPasoAPaso(boolean pasoAPaso);
    public void setBreakpoint(boolean breakpoint);
    public void creaImagen() throws VMException, FileNotFoundException, IOException;
    public Scanner getScanner();
}
