
CC = gcc
RM = rm
CFLAGS = -c -fmessage-length=0 -std=c99 
LIBS = -lm -lxml2 -lSDL
INCLUDES = -I /usr/include/libxml2/libxml -I /usr/include/SDL -I /usr/include/libxml2   
CSRCS = Board.c  Chess.c  ChessSDL.c  Game.c  General.c  GetMoves.c  miniMax.c  Piece.c  Player.c  ReadWriteXML.c  
CHDRS = Board.h  Chess.h  ChessSDL.h  Game.h  General.h  GetMoves.h  miniMax.h  Piece.h  Player.h  ReadWriteXML.h  
OBJS  = Board.o  Chess.o  ChessSDL.o  Game.o  General.o  GetMoves.o  miniMax.o  Piece.o  Player.o  ReadWriteXML.o 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

all: chessprog
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	$(CC) -o chessprog $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '	 

chessprog: $(OBJS) 

clean:
	$(RM) chessprog $(OBJS)

depend:
	makedepend -- $(CFLAGS) -- $(CSRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it.

Board.o: Board.h Piece.h General.h /usr/include/stdio.h
Board.o: /usr/include/features.h /usr/include/stdc-predef.h
Board.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Board.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
Board.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Board.o: /usr/include/_G_config.h /usr/include/wchar.h
Board.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
Board.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Board.o: /usr/include/string.h /usr/include/strings.h /usr/include/stdlib.h
Board.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Board.o: /usr/include/endian.h /usr/include/bits/endian.h
Board.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
Board.o: /usr/include/sys/types.h /usr/include/time.h
Board.o: /usr/include/sys/select.h /usr/include/bits/select.h
Board.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Board.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Board.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
Board.o: /usr/include/math.h /usr/include/bits/huge_val.h
Board.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Board.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Board.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Board.o: /usr/include/ctype.h /usr/include/memory.h
Chess.o: Chess.h miniMax.h General.h /usr/include/stdio.h
Chess.o: /usr/include/features.h /usr/include/stdc-predef.h
Chess.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Chess.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
Chess.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Chess.o: /usr/include/_G_config.h /usr/include/wchar.h
Chess.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
Chess.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Chess.o: /usr/include/string.h /usr/include/strings.h /usr/include/stdlib.h
Chess.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Chess.o: /usr/include/endian.h /usr/include/bits/endian.h
Chess.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
Chess.o: /usr/include/sys/types.h /usr/include/time.h
Chess.o: /usr/include/sys/select.h /usr/include/bits/select.h
Chess.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Chess.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Chess.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
Chess.o: /usr/include/math.h /usr/include/bits/huge_val.h
Chess.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Chess.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Chess.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Chess.o: /usr/include/ctype.h /usr/include/memory.h GetMoves.h Game.h Board.h
Chess.o: Piece.h Player.h
ChessSDL.o: ChessSDL.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
ChessSDL.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
ChessSDL.o: /usr/include/SDL/SDL_platform.h /usr/include/stdio.h
ChessSDL.o: /usr/include/features.h /usr/include/stdc-predef.h
ChessSDL.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ChessSDL.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
ChessSDL.o: /usr/include/bits/typesizes.h /usr/include/libio.h
ChessSDL.o: /usr/include/_G_config.h /usr/include/wchar.h
ChessSDL.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
ChessSDL.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ChessSDL.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ChessSDL.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ChessSDL.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ChessSDL.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
ChessSDL.o: /usr/include/time.h /usr/include/sys/select.h
ChessSDL.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
ChessSDL.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
ChessSDL.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
ChessSDL.o: /usr/include/bits/stdlib-float.h /usr/include/string.h
ChessSDL.o: /usr/include/inttypes.h /usr/include/stdint.h
ChessSDL.o: /usr/include/ctype.h /usr/include/iconv.h
ChessSDL.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
ChessSDL.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
ChessSDL.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
ChessSDL.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
ChessSDL.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
ChessSDL.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
ChessSDL.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
ChessSDL.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
ChessSDL.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
ChessSDL.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
ChessSDL.o: /usr/include/SDL/SDL_version.h General.h /usr/include/strings.h
ChessSDL.o: /usr/include/math.h /usr/include/bits/huge_val.h
ChessSDL.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
ChessSDL.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
ChessSDL.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
ChessSDL.o: /usr/include/memory.h /usr/include/unistd.h
ChessSDL.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
ChessSDL.o: /usr/include/getopt.h ReadWriteXML.h Chess.h miniMax.h GetMoves.h
ChessSDL.o: Game.h Board.h Piece.h Player.h
Game.o: Game.h Board.h Piece.h General.h /usr/include/stdio.h
Game.o: /usr/include/features.h /usr/include/stdc-predef.h
Game.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Game.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
Game.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Game.o: /usr/include/_G_config.h /usr/include/wchar.h
Game.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
Game.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Game.o: /usr/include/string.h /usr/include/strings.h /usr/include/stdlib.h
Game.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Game.o: /usr/include/endian.h /usr/include/bits/endian.h
Game.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
Game.o: /usr/include/sys/types.h /usr/include/time.h
Game.o: /usr/include/sys/select.h /usr/include/bits/select.h
Game.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Game.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Game.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
Game.o: /usr/include/math.h /usr/include/bits/huge_val.h
Game.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Game.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Game.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Game.o: /usr/include/ctype.h /usr/include/memory.h Player.h
General.o: General.h /usr/include/stdio.h /usr/include/features.h
General.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
General.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
General.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
General.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
General.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
General.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
General.o: /usr/include/string.h /usr/include/strings.h /usr/include/stdlib.h
General.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
General.o: /usr/include/endian.h /usr/include/bits/endian.h
General.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
General.o: /usr/include/sys/types.h /usr/include/time.h
General.o: /usr/include/sys/select.h /usr/include/bits/select.h
General.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
General.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
General.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
General.o: /usr/include/math.h /usr/include/bits/huge_val.h
General.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
General.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
General.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
General.o: /usr/include/ctype.h /usr/include/memory.h
GetMoves.o: GetMoves.h Game.h Board.h Piece.h General.h /usr/include/stdio.h
GetMoves.o: /usr/include/features.h /usr/include/stdc-predef.h
GetMoves.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
GetMoves.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
GetMoves.o: /usr/include/bits/typesizes.h /usr/include/libio.h
GetMoves.o: /usr/include/_G_config.h /usr/include/wchar.h
GetMoves.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
GetMoves.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
GetMoves.o: /usr/include/string.h /usr/include/strings.h
GetMoves.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
GetMoves.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
GetMoves.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
GetMoves.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
GetMoves.o: /usr/include/time.h /usr/include/sys/select.h
GetMoves.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
GetMoves.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
GetMoves.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
GetMoves.o: /usr/include/bits/stdlib-float.h /usr/include/math.h
GetMoves.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
GetMoves.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
GetMoves.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
GetMoves.o: /usr/include/bits/mathcalls.h /usr/include/ctype.h
GetMoves.o: /usr/include/memory.h Player.h
miniMax.o: miniMax.h General.h /usr/include/stdio.h /usr/include/features.h
miniMax.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
miniMax.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
miniMax.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
miniMax.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
miniMax.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
miniMax.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
miniMax.o: /usr/include/string.h /usr/include/strings.h /usr/include/stdlib.h
miniMax.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
miniMax.o: /usr/include/endian.h /usr/include/bits/endian.h
miniMax.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
miniMax.o: /usr/include/sys/types.h /usr/include/time.h
miniMax.o: /usr/include/sys/select.h /usr/include/bits/select.h
miniMax.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
miniMax.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
miniMax.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
miniMax.o: /usr/include/math.h /usr/include/bits/huge_val.h
miniMax.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
miniMax.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
miniMax.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
miniMax.o: /usr/include/ctype.h /usr/include/memory.h GetMoves.h Game.h
miniMax.o: Board.h Piece.h Player.h
Piece.o: Piece.h General.h /usr/include/stdio.h /usr/include/features.h
Piece.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
Piece.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Piece.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Piece.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
Piece.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
Piece.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Piece.o: /usr/include/string.h /usr/include/strings.h /usr/include/stdlib.h
Piece.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Piece.o: /usr/include/endian.h /usr/include/bits/endian.h
Piece.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
Piece.o: /usr/include/sys/types.h /usr/include/time.h
Piece.o: /usr/include/sys/select.h /usr/include/bits/select.h
Piece.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Piece.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Piece.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
Piece.o: /usr/include/math.h /usr/include/bits/huge_val.h
Piece.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Piece.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Piece.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Piece.o: /usr/include/ctype.h /usr/include/memory.h
Player.o: Player.h Piece.h General.h /usr/include/stdio.h
Player.o: /usr/include/features.h /usr/include/stdc-predef.h
Player.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Player.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
Player.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Player.o: /usr/include/_G_config.h /usr/include/wchar.h
Player.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
Player.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Player.o: /usr/include/string.h /usr/include/strings.h /usr/include/stdlib.h
Player.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Player.o: /usr/include/endian.h /usr/include/bits/endian.h
Player.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
Player.o: /usr/include/sys/types.h /usr/include/time.h
Player.o: /usr/include/sys/select.h /usr/include/bits/select.h
Player.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Player.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Player.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
Player.o: /usr/include/math.h /usr/include/bits/huge_val.h
Player.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Player.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Player.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Player.o: /usr/include/ctype.h /usr/include/memory.h
ReadWriteXML.o: ReadWriteXML.h Chess.h miniMax.h General.h
ReadWriteXML.o: /usr/include/stdio.h /usr/include/features.h
ReadWriteXML.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
ReadWriteXML.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ReadWriteXML.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ReadWriteXML.o: /usr/include/libio.h /usr/include/_G_config.h
ReadWriteXML.o: /usr/include/wchar.h /usr/include/bits/wchar.h
ReadWriteXML.o: /usr/include/xlocale.h /usr/include/bits/stdio_lim.h
ReadWriteXML.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
ReadWriteXML.o: /usr/include/strings.h /usr/include/stdlib.h
ReadWriteXML.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
ReadWriteXML.o: /usr/include/endian.h /usr/include/bits/endian.h
ReadWriteXML.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
ReadWriteXML.o: /usr/include/sys/types.h /usr/include/time.h
ReadWriteXML.o: /usr/include/sys/select.h /usr/include/bits/select.h
ReadWriteXML.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ReadWriteXML.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ReadWriteXML.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
ReadWriteXML.o: /usr/include/math.h /usr/include/bits/huge_val.h
ReadWriteXML.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
ReadWriteXML.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
ReadWriteXML.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
ReadWriteXML.o: /usr/include/ctype.h /usr/include/memory.h GetMoves.h Game.h
ReadWriteXML.o: Board.h Piece.h Player.h
