/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.utils;

/**
 *
 * @author valen
 */
public class IntUtils
{
    public static int getHigh(int valor)
    {
        return valor >> 16;
    }
    
    public static int getLow(int valor)
    {
        return (valor << 16) >> 16;
    }
}
