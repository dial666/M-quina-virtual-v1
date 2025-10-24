/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.operacionbinaria;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistro;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public class Div extends OperacionBinaria
{

    @Override
    public int cuenta(int valorA, int valorB)
    {
        return (int)(valorA / valorB);
    }
    
    @Override
    public void setAC(int valorA, int valorB, UnidadIO vm) 
    {
        OperandoRegistro opAC = new OperandoRegistroE(ConstantesRegistros.AC.getCodigo());
        opAC.setValor(vm, valorA % valorB);
    }

    @Override
    public String toString()
    {
        return "DIV";
    }
    
    
}
