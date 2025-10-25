/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys;

import java.io.IOException;
import java.util.Scanner;
import modelo.IDebuggeable;
import modelo.UnidadIO;
import modelo.excepciones.QuitException;
import modelo.excepciones.VMException;
import modelo.operacion.IOperacion;
import modelo.operando.Operando;

/**
 *
 * @author valen
 */
public class SysF implements IOperacion
{    
    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        IDebuggeable mvaux = (IDebuggeable) mv;
        if (mvaux.isAtenderDebugger())
            mvaux.setBreakpoint(true);
    }    
}
