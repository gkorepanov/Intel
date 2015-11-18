        scan
        pop ebx
        mov eax 2
	
	jmp loop2

loop1:
    call print_eax
	call eax_inc_2

loop2:  cmp ebx eax
        ja loop1

	end

proc print_eax
        push eax
        print
        pop
ret

proc eax_inc_2
        push eax
        push 2
        add
        pop eax
ret
