/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys;

import modelo.excepciones.VMException;
import modelo.operacion.sys.parser.IStringToNumberParser;
import modelo.operacion.sys.parser.StrToNmbBinario;
import modelo.operacion.sys.parser.StrToNmbCaracter;
import modelo.operacion.sys.parser.StrToNmbDecimal;
import modelo.operacion.sys.parser.StrToNmbHexadecimal;
import modelo.operacion.sys.parser.StrToNmbOctal;

/**
 *
 * @author valen
 */
public class Sys1 extends OperacionSysSimple
{
    IStringToNumberParser parser;
    
    @Override
    public void setParser(int modo) throw VMException
    {
        this.parser = switch (modo)
        {
            case 0x01 -> new StrToNmbDecimal();
            case 0x02 -> new StrToNmbCaracter();
            case 0x04 -> new StrToNmbOctal();
            case 0x08 -> new StrToNmbHexadecimal();
            case 0x10 -> new StrToNmbBinario();
            default -> throw new VMException("formato de sys desconocido");
       };
    }

    @Override
    public void manipularMem(int dirLogica, int tamCelda)
    {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }
    
}
