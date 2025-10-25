/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys.parser;

/**
 *
 * @author valen
 */
public abstract class NmbToStrCaracter implements INumberToStringParser
{

    @Override
    public String numberToString(int num, int tamCelda)
    {
        String cadena = "";
        int byteaux;
        
        for(int i =tamCelda-1; i>=0; i--)
        {
            byteaux = (num >> (i*8)) & 0xFF;
            if (condicionMostrarCar(byteaux))
                cadena += (char)(byteaux);
            else
                cadena += ".";
        }
        return cadena;
    }
    
    public abstract boolean condicionMostrarCar(int num);
}
