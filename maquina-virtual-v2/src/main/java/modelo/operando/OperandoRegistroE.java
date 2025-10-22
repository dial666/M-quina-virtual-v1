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
public class OperandoRegistroE extends OperandoRegistro
{

    public OperandoRegistroE(int codRegistro)
    {
        super(codRegistro, 0xFFFFFFFF, 0, 0);
    }

    @Override
    public String toString()
    {
        return ConstantesRegistros.getNombre(this.getCodRegistro());
    }
    
}
