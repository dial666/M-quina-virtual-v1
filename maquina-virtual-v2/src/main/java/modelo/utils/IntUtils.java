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
    public static int getHighSigned(int valor)
    {
        return valor >> 16;
    }
    
    public static int getLowSigned(int valor)
    {
        return (valor << 16) >> 16;
    }
    
    public static int getHighUnsigned(int valor)
    {
        return (valor >>> 16) & 0xFFFF;
    }
    
    public static int getLowUnsigned(int valor)
    {
        return valor & 0xFFFF;
    }
    
    public static int putHigh(int base, int valor)
    {
        return (base & 0x0000FFFF) | (valor << 16);
    }
    
    public static int putLow(int base, int valor)
    {
        return (base & 0xFFFF0000) | (valor & 0xFFFF);
    }
}
