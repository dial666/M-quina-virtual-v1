/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import javax.naming.OperationNotSupportedException;
import modelo.ConstantesRegistros;
import modelo.excepciones.SegmentationFaultException;
import modelo.UnidadIO;

/**
 *
 * @author valen
 */
public abstract class OperandoRegistro implements Operando
{
    private int codRegistro;
    private int mask;
    private int shift;
    private int shiftExtensionSigno;
    private int maskInicializa;
    
    public OperandoRegistro(int codRegistro, int mask, int shift, int shiftExtensionSigno, int maskInicializa)
    {
        this.codRegistro = codRegistro;
        this.mask = mask;
        this.shift = shift;
        this.shiftExtensionSigno = shiftExtensionSigno;
        this.maskInicializa = maskInicializa;
    }
    
    public int getCodRegistro()
    {
        return codRegistro;
    }

    public int getMask()
    {
        return mask;
    }

    public int getShift()
    {
        return shift;
    }

    public int getShiftExtensionSigno()
    {
        return shiftExtensionSigno;
    }

    public int getMaskInicializa()
    {
        return maskInicializa;
    }

    @Override
    public int getValor(UnidadIO vmx)
    {
        return vmx.getValor(this);
    }
    
    @Override
    public void setValor(UnidadIO vmx, int valor)
    {
       vmx.setValor(this, valor);
    }
}
