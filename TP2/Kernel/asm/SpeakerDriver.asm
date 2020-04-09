GLOBAL WritePITConfiguration
GLOBAL WritePIT2Data
GLOBAL ReadSpeakerData
GLOBAL WriteSpeakerData

section .text
WritePITConfiguration:
	enter 0,0

	mov rax,rdi

	out 43h,al

	leave
	ret

WritePIT2Data:
	enter 0,0

	mov rax,rdi

	out 42h,al

	leave
	ret

ReadSpeakerData:
	enter 0,0

	mov rax,0

	in al,61h


	leave
	ret

WriteSpeakerData:
	enter 0,0

	mov rax,rdi

	out 61h,al

	leave
	ret