/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys.parser;

/**
 *
 * @author valen
 */
public class NmbToStringCaracterMuestra0 extends NmbToStrCaracter
{

    @Override
    public boolean condicionMostrarCar(int num)
    {
        return num == 0 || num >= 32 && num <= 126;
    }
    
}
