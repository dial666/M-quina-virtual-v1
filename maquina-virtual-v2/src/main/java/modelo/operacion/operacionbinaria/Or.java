/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.operacionbinaria;

/**
 *
 * @author valen
 */
public class Or extends OperacionBinaria
{

    @Override
    public int cuenta(int valorA, int valorB)
    {
        return valorA | valorB;
    }

    @Override
    public String toString()
    {
        return "OR";
    }
    
    
}
