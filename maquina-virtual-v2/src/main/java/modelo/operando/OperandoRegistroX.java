/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import modelo.ConstantesRegistros;

/**
 *
 * @author valen
 */
public class OperandoRegistroX extends OperandoRegistro
{

    public OperandoRegistroX(int codRegistro)
    {
        super(codRegistro, 0xFFFF, 0, 16);
    }

    @Override
    public String toString()
    {
        String letra = ConstantesRegistros.getNombre(this.getCodRegistro()).substring(1, 2);
        return letra + "X";
    }
    
}
