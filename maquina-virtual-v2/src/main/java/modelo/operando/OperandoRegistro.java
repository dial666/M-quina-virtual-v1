/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import javax.naming.OperationNotSupportedException;
import modelo.ConstantesRegistros;
import modelo.Contexto;
import modelo.excepciones.SegmentationFaultException;

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
    
    public OperandoRegistro(int codRegistro, int mask, int shift, int shiftExtensionSigno)
    {
        this.codRegistro = codRegistro;
        this.mask = mask;
        this.shift = shift;
        this.shiftExtensionSigno = shiftExtensionSigno;
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

    @Override
    public int getValor(Contexto vmx)
    {
        int valor = 0;
        try
        {
            valor = vmx.getValor(this);
        } 
        catch (SegmentationFaultException e)
        {
            throw new IllegalStateException("no deberia ocurrir un segmentation fault en un registro");
        }
        return valor;
    }
    
    public int setValor(Contexto vmx) throws SegmentationFaultException, IllegalArgumentException
    {
       return 0;
    }
}
