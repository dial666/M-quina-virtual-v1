/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys.parser;

/**
 *
 * @author valen
 */
public class NmbToStrOctal implements INumberToStringParser
{

    @Override
    public String numberToString(int num, int tamCelda)
    {
        return "0o" + Integer.toOctalString(num);
    }
    
}
