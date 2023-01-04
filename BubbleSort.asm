.686
.model flat

.data
	numSort DWORD ?			;var to hold sorting order
.code

_masmBubbleSort PROC		;named _masmBubbleSort because C automatically prepends an underscode, it is needed to interoperate

	push ebp
	mov ebp,esp				;stack pointer
	
	mov ebx, [ebp+8]		;masmBubble( assemblyArr,...,...)
	mov ecx, [ebp+12]		;masmBubble(..., SIZE,...)
	mov edx, [ebp+16]		;masmBubble(...,..., sortOrder)

	dec ecx					;offset array size
	mov eax, 0				;increment set to 0
	cmp edx, 0				;check on sorting choice 0 for ascending, 1 for descending
	je SetValueZero			;if 0, numSort = 0
	jmp SetValueOne			;if 1, numsort = 1
	
SetValueZero:				
	mov numSort, 0			;numSort = 0
	jmp AscendingMainLoop	;go to Ascending loop	

SetValueOne:				
	mov numSort, 1			;numSort = 1
	jmp DescendingMainLoop	;go to Descending loop
	
AscendingMainLoop:
	cmp eax, ecx 			;Compare assemblyArr[i] with SIZE
	je Done					;Current assemblyArr[i] = assemblyArr[SIZE] we're done. 
	add eax, 1				;If not increment i++
	mov edx, 0				;Set edx to 0 and use it for byte increment of +4
	mov ebp, 0				;Set Adjacent increment to 0, j++

AscendingAdjLoop:
	cmp ebp, ecx			;Compare assemblyArr[j] with SIZE
	je AscendingMainLoop	;Current assemblyArr[j] = assemblyArr[SIZE] we're done. 
	mov esi,[ebx+edx]		;Move assemblyArr[j]
	cmp esi, [ebx+edx+4]	;Compare assemblyArr[j] with the next value
	jg AscendingSwap		;If assemblyArr[j] is greater than the next value call swap
	jmp IndexIncrement		;If not increment index +1

AscendingSwap:			
	mov edi, [ebx+edx+4]	;Move assemblyArr[j+1] into edi
	mov [ebx+edx], edi		;assemblyArr[j] = assemblyArr[j+1]
	mov [ebx+edx+4], esi	;assemblyArr[j+1] = assembly[j]
	jmp IndexIncrement		;goto IndexIncrement

DescendingMainLoop:	
	cmp eax, ecx			;Compare assemblyArr[i] with SIZE
	je Done					;Current assemblyArr[i] = assemblyArr[SIZE] we're done.
	add eax, 1				;If not increment i++
	mov edx, 0				;Set edx to 0 and use it for byte increment of +4
	mov ebp, 0				;Set Adjacent increment to 0, j++

DescendingAdjLoop:
	cmp ebp, ecx			;Compare assemblyArr[j] with SIZE
	je DescendingMainLoop	;Current assemblyArr[j] = assemblyArr[SIZE] we're done. 
	mov esi,[ebx+edx]		;Move assemblyArr[j]
	cmp esi, [ebx+edx+4]	;Compare assemblyArr[j] with the next value
	jl DescendingSwap		;If assemblyArr[j] is greater than the next value call swap
	jmp IndexIncrement		;If not increment index +1

DescendingSwap:			
	mov edi, [ebx+edx+4]	;Move assemblyArr[j+1] into edi
	mov [ebx+edx], edi		;assemblyArr[j] = assemblyArr[j+1]
	mov [ebx+edx+4], esi	;assemblyArr[j+1] = assembly[j]		

IndexIncrement:
	inc ebp					;j++
	add edx, 4				;go to the next memory by +4
	cmp numSort, 0			;check sorting option 0 or a 1
	je AscendingAdjLoop		;ascending sort if its 0
	jmp DescendingAdjLoop	;descending sort if its 1

Done:	
	pop ebp
	ret

_masmBubbleSort ENDP

END