/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.utils;

/**
 *
 * @author valen
 */
public class StringUtils
{
    public static String getEspacios(int espacioTotal, String cadena)
    {
        String espacios = "";
        int i = cadena.length();
        for(; i < espacioTotal; i++)
            espacios += " ";
        return espacios;
    }
}
