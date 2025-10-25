/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys.parser;

/**
 *
 * @author valen
 */
public class StrToNmbCaracter implements IStringToNumberParser
{

    @Override
    public int StringToNumber(String cadena)
    {
        int n = cadena.length();
        int num = 0;
        for (int i = 0; i < n; i++)
          num = (num << 8) | (byte) (cadena.charAt(i));
        return num;
    }
    
}
