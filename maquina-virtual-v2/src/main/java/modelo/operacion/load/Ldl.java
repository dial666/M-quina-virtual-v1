/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.load;

import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public class Ldl extends OperacionLoad
{

    @Override
    public int cuenta(int valorA, int valorB)
    {
        return IntUtils.putLow(valorA, IntUtils.getLowUnsigned(valorB));
    }

    @Override
    public String toString()
    {
        return "LDL";
    }
 
}
