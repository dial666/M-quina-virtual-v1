/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys.parser;

import modelo.operacion.sys.parser.IStringToNumberParser;

/**
 *
 * @author valen
 */
public class StrToNmbBinario implements IStringToNumberParser
{

    @Override
    public int StringToNumber(String cadena)
    {
        return Integer.parseInt(cadena, 2);
    }
    
}
