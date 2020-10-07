
void mmio_write(unsigned long address, int offset, char value)
{
	// We use volatile so that the optimizer on the
	// compiler doesn't think we're writing a value for
	// no reason.
	volatile char *reg = (char *)address;

	// To write, the pointer is on the left hand side of
	// the assignment operator.
	// Transmit the word 'A'
	// (which is the 8-bit value 65 or 0b0100_0001)
	*(reg + offset) = value;
}

char mmio_read(unsigned long address, int offset)
{
	// We use volatile so that the optimizer on the
	// compiler doesn't think we're writing a value for
	// no reason.
	volatile char *reg = (char *)address;

	// To read, the pointer is dereferenced on a read.
	// This reads from the receiver and returns the data.
	return *(reg + offset);
}

void uart_init(unsigned long base_addres)
{

	
}
