/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.operacionbinaria;

import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operando.Operando;

/**
 *
 * @author valen
 */
public class Cmp extends OperacionBinaria
{

    @Override
    public int cuenta(int valorA, int valorB)
    {
        return valorA - valorB;
    }
    
    @Override
    public void setValor(Operando opA, int resultado, UnidadIO mv) throws VMException
    {
        
    }

    @Override
    public String toString()
    {
        return "CMP";
    }
    
    
}
