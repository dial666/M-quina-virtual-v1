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
 * @author valen
 */
public class OperacionSys implements IOperacion
{
    IOperacion operacion;

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        int tipoSys = opA.getValor(mv);
        this.operacion = switch (tipoSys)
        {
            case 1 -> new Sys1();
            case 2 -> new Sys2();
            case 3 -> new Sys3();
            case 4 -> new Sys4();
            case 7 -> new Sys7();
            case 0xF -> new SysF();
            default -> throw new VMException("tipo de sys desconocido");
        };
        this.operacion.ejecutar(opA, opB, mv);
    }

    @Override
    public String toString()
    {
        return "SYS";
    }
    
    
}
