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
public class OperandoRegistroH extends OperandoRegistro
{

    public OperandoRegistroH(int codRegistro)
    {
        super(codRegistro, 0xFF, 8, 16, 0xFFFF00FF);
    }

    @Override
    public String toString()
    {
        String letra = ConstantesRegistros.getNombre(this.getCodRegistro()).substring(1, 2);
        return letra + "H";
    }
    
}
