//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// 3D.c - [Maths Handling Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define	ID_TMD	0x00000041
#define	ID_PMD	0x00000050
#define	ID_FIXP	0x00000001


#define	G3D_IntVector( r0, r1 ) __asm__ volatile ( \
	"lw	$12, 0( %1 );"	\
	"lw	$13, 4( %1 );"	\
	"lw	$14, 8( %1 );"	\
	"srl	$12, 12;"		\
	"srl	$13, 12;"		\
	"srl	$14, 12;"		\
	"sw	$12, 0( %0 );"	\
	"sw	$13, 4( %0 );"	\
	"sw	$14, 8( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_IntSVector( r0, r1 ) __asm__ volatile ( \
	"lw	$12, 0( %1 );"	\
	"lw	$13, 4( %1 );"	\
	"lw	$14, 8( %1 );"	\
	"srl	$12, 12;"		\
	"srl	$13, 12;"		\
	"srl	$14, 12;"		\
	"sh	$12, 0( %0 );"	\
	"sh	$13, 2( %0 );"	\
	"sh	$14, 4( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_RealSVector( r0, r1 ) __asm__ volatile ( \
	"lh	$12, 0( %1 );"	\
	"lh	$13, 2( %1 );"	\
	"lh	$14, 4( %1 );"	\
	"sll	$12, 12;"		\
	"sll	$13, 12;"		\
	"sll	$14, 12;"		\
	"sw	$12, 0( %0 );"	\
	"sw	$13, 4( %0 );"	\
	"sw	$14, 8( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_CopySVectorV3D( r0, r1 ) __asm__ volatile ( \
	"lh	$12, 0( %1 );"	\
	"lh	$13, 2( %1 );"	\
	"lh	$14, 4( %1 );"	\
	"sw	$12, 0( %0 );"	\
	"sw	$13, 4( %0 );"	\
	"sw	$14, 8( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_CopySVector( r0, r1 ) __asm__ volatile ( \
	"lh	$12, 0( %1 );"	\
	"lh	$13, 2( %1 );"	\
	"lh	$14, 4( %1 );"	\
	"sw	$12, 0( %0 );"	\
	"sw	$13, 4( %0 );"	\
	"sw	$14, 8( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_CopyVector( r0, r1 ) __asm__ volatile ( \
	"lw	$12, 0( %1 );"	\
	"lw	$13, 4( %1 );"	\
	"lw	$14, 8( %1 );"	\
	"sw	$12, 0( %0 );"	\
	"sw	$13, 4( %0 );"	\
	"sw	$14, 8( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_CopyV3DSVector( r0, r1 ) __asm__ volatile ( \
	"lw	$12, 0( %1 );"	\
	"lw	$13, 4( %1 );"	\
	"lw	$14, 8( %1 );"	\
	"sh	$12, 0( %0 );"	\
	"sh	$13, 2( %0 );"	\
	"sh	$14, 4( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_RealVector( r0, r1 ) __asm__ volatile ( \
	"lw	$12, 0( %1 );"	\
	"lw	$13, 4( %1 );"	\
	"lw	$14, 8( %1 );"	\
	"sll	$12, 12;"		\
	"sll	$13, 12;"		\
	"sll	$14, 12;"		\
	"sw	$12, 0( %0 );"	\
	"sw	$13, 4( %0 );"	\
	"sw	$14, 8( %0 )"	\
	:							\
	: "r"(r0), "r"(r1)	\
	: "$12", "$13", "$14", "memory")

#define	G3D_SetVector( r0, r1, r2, r3 ) __asm__ volatile ( \
	"sw	%1, 0( %0 );"	\
	"sw	%2, 4( %0 );"	\
	"sw	%3, 8( %0 )"	\
	:							\
	: "r"(r0), "r"(r1), "r"(r2), "r"(r3) \
	: "memory")

#define	G3D_SetSVector( r0, r1, r2, r3 ) __asm__ volatile ( \
	"sh	%1, 0( %0 );"	\
	"sh	%2, 2( %0 );"	\
	"sh	%3, 4( %0 )"	\
	:							\
	: "r"(r0), "r"(r1), "r"(r2), "r"(r3) \
	: "memory")

#define	G3D_ClearVector( r0 ) __asm__ volatile ( \
	"sw	$0, 0( %0 );"	\
	"sw	$0, 4( %0 );"	\
	"sw	$0, 8( %0 );"	\
	"sw	$0, 12( %0 )"	\
	:							\
	: "r"( r0 )				\
	: "memory")

#define	G3D_ClearSVector( r0 ) __asm__ volatile ( \
	"sw	$0, 0( %0 );"	\
	"sw	$0, 4( %0 )"	\
	:							\
	: "r"( r0 )				\
	: "memory")

// Inline ApplyRotMatrix Function
#define	G3D_ApplyRotMatrix( r0, r1 ) __asm__ volatile ( \
	"lw	$12, 0( %0 );"	\
	"lw	$13, 4( %0 );"	\
	"mtc2	$12, $0;"		\
	"mtc2	$13, $1;"		\
	"nop;"					\
	".word	0x4a486012;"	\
	"swc2	$9, 0( %1 );"	\
	"swc2	$10, 4( %1 );"	\
	"swc2	$11, 8( %1 )"	\
	:							\
	: "r"( r0 ), "r"( r1 )	\
	: "$12", "$13", "memory")


#define	G3D_OuterProduct0( r0, r1, r2 ) __asm__ volatile ( \
	"cfc2	$12, $0;"	\
	"cfc2	$13, $2;"	\
	"cfc2	$14, $4;"	\
	"lw $8, 0( %0 );"	\
	"lw $9, 4( %0 );"	\
	"lw $10, 8( %0 );"	\
	"ctc2 $8, $0;"		\
	"ctc2 $9, $4;"		\
	"ctc2 $10, $8;"	\
	"lwc2 $9, 0( %1 );"	\
	"lwc2 $10, 4( %1 );"	\
	"lwc2 $11, 8( %1 );"	\
	"nop;"				\
	".word	0x4b70000c;"	\
	"swc2 $25, 0( %2 );"	\
	"swc2 $26, 4( %2 );"	\
	"swc2 $27, 8( %2 );"	\
	"ctc2	$12, $0;"	\
	"ctc2	$13, $2;"	\
	"ctc2	$14, $4;"	\
	:						\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )	\
	: "$12", "$13", "$14", "$8", "$9", "$10", "memory")


#define	G3D_SetRotMatrix( r0 ) __asm__ volatile ( \
	"lw	$8, 0( %0 );"	\
	"lw	$9, 4( %0 );"	\
	"lw	$10, 8( %0 );"	\
	"lw	$11, 12( %0 );"	\
	"lw	$12, 16( %0 );"	\
	"ctc2	$8, $0;"	\
	"ctc2	$9, $1;"	\
	"ctc2	$10, $2;"	\
	"ctc2	$11, $3;"	\
	"ctc2	$12, $4;"	\
	:		\
	: "r"( r0 )	\
	: "$8", "$9", "$10", "$11", "$12", "memory")

#define	G3D_SetTransMatrix( r0 ) __asm__ volatile ( \
	"lw	$8, 0( %0 );"	\
	"lw	$9, 4( %0 );"	\
	"lw	$10, 8( %0 );"	\
	"ctc2	$8, $5;"	\
	"ctc2	$9, $6;"	\
	"ctc2	$10, $7;"	\
	:		\
	: "r"( r0 )	\
	: "$8", "$9", "$10", "memory")


Uint32	G3D_absmax(Sint32 a,Sint32 b,Sint32 c);

