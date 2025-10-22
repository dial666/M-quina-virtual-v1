/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import modelo.ConstantesRegistros;
import modelo.excepciones.SegmentationFaultException;
import modelo.UnidadIO;

/**
 *
 * @author valen
 */
public class OperandoRegistroL extends OperandoRegistro
{

    public OperandoRegistroL(int codRegistro)
    {
        super(codRegistro, 0xFF, 0, 24);
    }

    @Override
    public String toString()
    {
        String letra = ConstantesRegistros.getNombre(this.getCodRegistro()).substring(1, 2);
        return letra + "L";
    }  
}
