/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys;

import java.util.ArrayList;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operacion.sys.parser.INumberToStringParser;
import modelo.operacion.sys.parser.NmbToStrBinario;
import modelo.operacion.sys.parser.NmbToStrCaracter;
import modelo.operacion.sys.parser.NmbToStrDecimal;
import modelo.operacion.sys.parser.NmbToStrHexadecimal;
import modelo.operacion.sys.parser.NmbToStrOctal;
import modelo.operacion.sys.parser.NmbToStringCaracterNoMuestra0;

/**
 *
 * @author valen
 */
public class Sys2 extends OperacionSysSimple
{
    ArrayList<INumberToStringParser> parsers;
    
    public Sys2()
    {
        this.parsers = new ArrayList<>();
    }
    
    @Override
    public void setParser(int modo) throws VMException
    {
        if ((modo & 0x08) != 0)
            this.parsers.add(new NmbToStrHexadecimal());
        if ((modo & 0x04) != 0)
            this.parsers.add(new NmbToStrOctal());
        if ((modo & 0x02) != 0)
            this.parsers.add(new NmbToStringCaracterNoMuestra0());
        if ((modo & 0x01) != 0)
            this.parsers.add(new NmbToStrDecimal());
        if ((modo & 0x10) != 0)
            this.parsers.add(new NmbToStrBinario());
        if (this.parsers.isEmpty())
            throw new VMException("formato de sys desconocido");
    }

    @Override
    public void manipularMem(int dirLogica, int tamCelda, UnidadIO mv) throws VMException
    {
        int valor = mv.getValorMemoriaModificaReg(dirLogica, tamCelda);
        String cadena = "";
        for (INumberToStringParser parser: this.parsers)
            cadena += parser.numberToString(valor, tamCelda) + " ";
        System.out.println(cadena);
    }
    
}
