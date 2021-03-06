#ifndef UNITTEST_HPP
#define UNITTEST_HPP

#ifndef NDEBUG		// ifndef NDEBUG

#include <iostream>
#include <cassert>	// Debug assertion
#include <bitset>
#include "SignedBitset.hpp"
#include "Exceptions.hpp"

#include "SynchrotronComponent.hpp"

#include "ANDGate.hpp"
#include "NANDGate.hpp"
#include "ORGate.hpp"
#include "NORGate.hpp"
#include "XORGate.hpp"
#include "NOTGate.hpp"
#include "MemoryCell.hpp"
#include "SHIFTLeft.hpp"
#include "SHIFTRight.hpp"
#include "Memory.hpp"
#include "Clock.hpp"

using namespace CPUComponents;

/*
 *	Constant bit values.
 */
static std::bitset<1>	one_bit_0 = 0,	// 0
						one_bit_1 = 1;	// 1
static std::bitset<2>	two_bit_0 = 0,	// 00
						two_bit_1 = 1,	// 01
						two_bit_2 = 2,	// 10
						two_bit_3 = 3;	// 11
static std::bitset<3>	thr_bit_0 = 0,	// 000
						thr_bit_1 = 1,	// 001
						thr_bit_2 = 2,	// 010
						thr_bit_3 = 3,	// 011
						thr_bit_4 = 4,	// 100
						thr_bit_5 = 5,	// 101
						thr_bit_6 = 6,	// 110
						thr_bit_7 = 7;	// 111
static std::bitset<4>	for_bit_0 = 0,	// 0000
						for_bit_1 = 1,	// 0001
						for_bit_2 = 2,	// 0010
						for_bit_3 = 3,	// 0011
						for_bit_4 = 4,	// 0100
						for_bit_5 = 5,	// 0101
						for_bit_7 = 7,	// 0111
						for_bit_8 = 8,	// 1000
						for_bit_A = 10,	// 1010
						for_bit_B = 11,	// 1011
						for_bit_F = 15;	// 1111

/*
 *	Constant signals and signal providers.
 */
static SynchrotronComponent<1>	signal1_0(one_bit_0.to_ulong()),					// 0
								signal1_0_(one_bit_0.to_ulong()),					// 0 other unique
								signal1_1(one_bit_1.to_ulong()),					// 1
								signal1_1_(one_bit_1.to_ulong());					// 1 other unique
static SynchrotronComponent<2>	signal2_0(two_bit_0.to_ulong()),					// 00
								signal2_0_(two_bit_0.to_ulong()),					// 00 other unique
								signal2_1(two_bit_1.to_ulong()),					// 01
								signal2_1_(two_bit_1.to_ulong()),					// 01 other unique
								signal2_2(two_bit_2.to_ulong()),					// 10
								signal2_3(two_bit_3.to_ulong());					// 11
static SynchrotronComponent<4>	signal4_8( for_bit_8.to_ulong() ),					// 1000
								signal4_A( for_bit_A.to_ulong() );					// 1010
static SynchrotronComponent<1>	signalProvider1_0_0( {&signal1_0, &signal1_0_} ),	// 0 0
								signalProvider1_0_1( {&signal1_0, &signal1_1} ),	// 0 1
								signalProvider1_1_0( {&signal1_1, &signal1_0} ),	// 1 0
								signalProvider1_1_1( {&signal1_1, &signal1_1_} );	// 1 1
static SynchrotronComponent<2>	signalProvider2_0_0( {&signal2_0, &signal2_0_} ),	// 00 00
								signalProvider2_0_1( {&signal2_0, &signal2_1} ),	// 00 01
								signalProvider2_1_0( {&signal2_1, &signal2_0} ),	// 01 00
								signalProvider2_1_1( {&signal2_1, &signal2_1_} ),	// 01 01
								signalProvider2_0_2( {&signal2_0, &signal2_2} ),	// 00 10
								signalProvider2_1_2( {&signal2_1, &signal2_2} ),	// 01 10
								signalProvider2_0_3( {&signal2_0, &signal2_3} ),	// 00 11
								signalProvider2_1_3( {&signal2_1, &signal2_3} );	// 01 11

/*
 *	Bitset : Test basic bitset methods to show how they work.
 */
void testBitset(void) {
	// Needs fixed size at compile time.
	std::bitset<4> x = 0xA, y;

	assert(x == for_bit_A);
	std::cout << "x             : " << x				<< std::endl;

	assert(x.to_ulong() == 10ul);
	std::cout << "As ulong      : " << x.to_ulong()		<< std::endl;

	assert(x.to_string() == "1010");
	std::cout << "As string     : " << x.to_string()	<< std::endl;

	std::cout << "x |= 4        = " << (x |= 4)			<< std::endl;
	assert(x == 0xE);

	std::cout << "x invert      = " << x.flip()			<< std::endl;
	assert(x == for_bit_1);

	std::cout << "x count       = " << x.count()		<< std::endl;
	assert(x.count() == 1);

	std::cout << "x any (| all) = " << x.any()			<< std::endl; // OR
	assert(x.any() == true);

	std::cout << "x all (& all) = " << x.all()			<< std::endl; // AND
	assert(x.all() == false);

	std::cout << "x none(~|all) = " << x.none()			<< std::endl; // NOR
	assert(x.all() == false);

	std::cout << "x test.0      = " << x.test(0)		<< std::endl;
	assert(x.test(0) == true);

	std::cout << "x test.3      = " << x.test(3)		<< std::endl;
	assert(x.test(3) == false);

	std::cout << "x size        = " << x.size()			<< std::endl;
	assert(x.size() == 4);

	std::cout << "x reset       = " << x.reset()		<< std::endl;
	assert(x == for_bit_0);

	std::cout << "x count       = " << x.count()		<< std::endl;
	assert(x.count() == 0);

	std::cout << "x set         = " << x.set()			<< std::endl;
	assert(x == for_bit_F);

	std::cout << "x set.3=0     = " << x.set(3, false)	<< std::endl;
	assert(x == 0x7);

	std::cout << "x << 1        = " << x.operator <<(1)	<< std::endl;
	assert(x == 0x7);	// 0111

	y = for_bit_A;		// 1010
	assert((x & y) == 0x2);
}

// TO-DO
//void testSignedBitset(void) {
//	SignedBitset<4> x(-1);
//}


/*
 *	SynchrotronComponent : Test SynchrotronComponent class.
 */
void testSynchrotronComponent(void) {
	SynchrotronComponent<4>	s_with_null,
							s_with_1(for_bit_1.to_ulong()),
							s_with_2(for_bit_2.to_ulong()),
							s_sign_1(for_bit_1.to_ulong()),
							*s_pointed = new SynchrotronComponent<4>(for_bit_2.to_ulong());

	assert(s_pointed != nullptr);

	assert(s_with_null.getState()				== for_bit_0);
	assert(s_with_null.getBitWidth()			== 4);
	assert(s_with_null.getInputs().size()		== 0);
	assert(s_with_null.getOutputs().size()		== 0);
	assert(s_with_1.getState()					== for_bit_1);
	assert(s_with_1.getBitWidth()				== 4);
	assert(s_with_1.getInputs().size()			== 0);
	assert(s_with_1.getOutputs().size()			== 0);
	assert(s_pointed->getState()				== for_bit_2);
	assert(s_pointed->getBitWidth()				== 4);
	assert(s_pointed->getInputs().size()		== 0);
	assert(s_pointed->getOutputs().size()		== 0);

	s_with_null.addOutput( {&s_with_1, &s_with_2} );
	assert(s_with_null.getOutputs().size()		== 2);
	s_with_null.addOutput(s_with_1); // Add again to see if size() increases, it should not.
	assert(s_with_null.getOutputs().size()		== 2);
	assert(s_with_1.getInputs().size()			== 1);
	s_with_1.addInput(s_with_null); // Add again to see if size() increases, it should not.
	assert(s_with_1.getInputs().size()			== 1);
	assert(s_with_2.getInputs().size()			== 1);

	s_with_null.emit();	// Internal State is 0x0, gets ORed to subscribers
	assert(s_with_1.getState()					== for_bit_1);

	s_with_null.addInput(*s_pointed);
	assert(s_with_null.getInputs().size()		== 1);
	assert(s_pointed->getOutputs().size()		== 1);
	s_pointed->emit(); // Internal State is 0x2, gets ORed to subscribers
	assert(s_with_null.getState()				== for_bit_2); // tick()ed by s_pointed
	assert(s_with_1.getState()					== for_bit_3); // tick()ed by s_with_null = 0x2 | 0x1
	assert(s_with_2.getState()					== for_bit_2);

	s_with_1.removeInput(s_with_null);
	assert(s_with_1.getInputs().size()			== 0);
	assert(s_with_null.getOutputs().size()		== 1);
	s_with_null.removeOutput(s_with_1); // Remove again to see if size() decreases, it should not.
	assert(s_with_null.getOutputs().size()		== 1);

	s_sign_1.addOutput(s_with_null);
	assert(s_with_null.getInputs().size()		== 2);
	assert(s_sign_1.getOutputs().size()			== 1);
	s_with_null.tick();	// Should update from 0x2 to 0x3 (==> s_sign_1(1) | s_pointed(2) == 3)
	assert(s_with_null.getState()				== for_bit_3);
	assert(s_with_1.getState()					== for_bit_3); // unchanged
	assert(s_with_2.getState()					== for_bit_3); // tick()ed by s_with_null = 0x3 | 0x2

	// flow: {s_pointed, s_sign_1} -> s_with_null -> s_with_2
	SynchrotronComponent<4>	s_copy_sign(s_with_2);
	// flow: {s_pointed, s_sign_1} -> s_with_null -> {s_with_2, s_copy_sign}

	assert(s_copy_sign.getInputs().size()		== 1);
	assert(s_copy_sign.getOutputs().size()		== 0);
	assert(s_with_null.getOutputs().size()		== 2);
	assert(s_copy_sign.getState()				== for_bit_0);
	s_with_null.emit();
	assert(s_copy_sign.getState()				== for_bit_3);

	{	// Create components in block to check dtors after block
		SynchrotronComponent<4>	s_copy_both(s_with_null, true),
								s_with_8(for_bit_8.to_ulong());
		// flow: {s_pointed, s_sign_1} -> {s_with_null, s_copy_both} -> {s_with_2, s_copy_sign}
		s_copy_both.addInput(s_with_8);
		// flow:              s_with_8 -> s_copy_both

		assert(s_with_8.getInputs().size()		== 0);
		assert(s_with_8.getOutputs().size()		== 1);
		assert(s_copy_both.getInputs().size()	== 3);
		assert(s_copy_both.getOutputs().size()	== 2);
		assert(s_copy_sign.getInputs().size()	== 2);
		assert(s_with_2.getInputs().size()		== 2);
		assert(s_pointed->getOutputs().size()	== 2);
		assert(s_sign_1.getOutputs().size()		== 2);
		s_with_8.emit();
		assert(s_copy_both.getState()			== for_bit_B); // tick()ed by s_with_8    = 0x0 | 0x8 | 0x3
		assert(s_with_2.getState()				== for_bit_B); // tick()ed by s_copy_both = 0x3 | 0x8
		assert(s_copy_sign.getState()			== for_bit_B); // tick()ed by s_copy_both = 0x3 | 0x8
	}	// s_copy_both and s_with_8 destructed => connections should be gone

	// flow: {s_pointed, s_sign_1} -> s_with_null -> {s_with_2, s_copy_sign}
	assert(s_pointed->getOutputs().size()		== 1);
	assert(s_sign_1.getOutputs().size()			== 1);
	assert(s_copy_sign.getInputs().size()		== 1);
	assert(s_with_2.getInputs().size()			== 1);

	delete s_pointed;
}

/*
 *	AND Gate : Test basic logic.
 */
void testLogic_AND_const(void) {
	ANDGate<1>	g1_0_0(signalProvider1_0_0),
				g1_0_1(signalProvider1_0_1),
				g1_1_0(signalProvider1_1_0),
				g1_1_1(signalProvider1_1_1);
	ANDGate<2>	g2_0_0(signalProvider2_0_0),
				g2_0_1(signalProvider2_0_1),
				g2_1_0(signalProvider2_1_0),
				g2_1_1(signalProvider2_1_1),
				g2_0_2(signalProvider2_0_2),
				g2_1_2(signalProvider2_1_2),
				g2_0_3(signalProvider2_0_3),
				g2_1_3(signalProvider2_1_3);

	// AND Gate with width 1 (2 inputs)
	assert(g1_0_0.getState()			== one_bit_0);
	g1_0_0.tick();
	assert(g1_0_0.getState()			== one_bit_0);

	assert(g1_0_1.getState()			== one_bit_0);
	g1_0_1.tick();
	assert(g1_0_1.getState()			== one_bit_0);

	assert(g1_1_0.getState()			== one_bit_0);
	g1_1_0.tick();
	assert(g1_1_0.getState()			== one_bit_0);

	assert(g1_1_1.getState()			== one_bit_0);
	g1_1_1.tick();
	assert(g1_1_1.getState()			== one_bit_1);	// Output changed to 1 after tick()

	// AND Gate with width 2 (2 inputs)
	assert(g2_0_0.getState()			== two_bit_0);
	g2_0_0.tick();
	assert(g2_0_0.getState()			== two_bit_0);

	assert(g2_0_1.getState()			== two_bit_0);
	g2_0_1.tick();
	assert(g2_0_1.getState()			== two_bit_0);

	assert(g2_1_0.getState()			== two_bit_0);
	g2_1_0.tick();
	assert(g2_1_0.getState()			== two_bit_0);

	assert(g2_1_1.getState()			== two_bit_0);
	g2_1_1.tick();
	assert(g2_1_1.getState()			== two_bit_1);	// Output changed to 1 after tick()

	assert(g2_0_2.getState()			== two_bit_0);
	g2_0_2.tick();
	assert(g2_0_2.getState()			== two_bit_0);

	assert(g2_1_2.getState()			== two_bit_0);
	g2_1_2.tick();
	assert(g2_1_2.getState()			== two_bit_0);

	assert(g2_0_3.getState()			== two_bit_0);
	g2_0_3.tick();
	assert(g2_0_3.getState()			== two_bit_0);

	assert(g2_1_3.getState()			== two_bit_0);
	g2_1_3.tick();
	assert(g2_1_3.getState()			== two_bit_1);	// Output changed to 1 after tick()
}

/*
 *	AND Gate : Test dynamic logic.
 */
void testLogic_AND_dynamic(void) {
	ANDGate<2> g2;

	g2.addInput( {&signal2_0, &signal2_0_} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_0);
	g2.removeInput(signal2_0);
	g2.removeInput(signal2_0_);
	assert(g2.getInputs().size()		== 0);

	g2.addInput( {&signal2_1, &signal2_2} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_0);
	g2.removeInput(signal2_2);
	assert(g2.getInputs().size()		== 1);

	g2.addInput(signal2_3);
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_1);
	g2.removeInput(signal2_1);
	g2.removeInput(signal2_3);
	assert(g2.getInputs().size()		== 0);
}

/*
 *	NAND Gate : Test basic logic.
 */
void testLogic_NAND_const(void) {
	NANDGate<1>	g1_0_0(signalProvider1_0_0),
				g1_0_1(signalProvider1_0_1),
				g1_1_0(signalProvider1_1_0),
				g1_1_1(signalProvider1_1_1);
	NANDGate<2>	g2_0_0(signalProvider2_0_0),
				g2_0_1(signalProvider2_0_1),
				g2_1_0(signalProvider2_1_0),
				g2_1_1(signalProvider2_1_1),
				g2_0_2(signalProvider2_0_2),
				g2_1_2(signalProvider2_1_2),
				g2_0_3(signalProvider2_0_3),
				g2_1_3(signalProvider2_1_3);

	// NAND Gate with width 1 (2 inputs)
	assert(g1_0_0.getState()			== one_bit_0);
	g1_0_0.tick();
	assert(g1_0_0.getState()			== one_bit_1);

	assert(g1_0_1.getState()			== one_bit_0);
	g1_0_1.tick();
	assert(g1_0_1.getState()			== one_bit_1);

	assert(g1_1_0.getState()			== one_bit_0);
	g1_1_0.tick();
	assert(g1_1_0.getState()			== one_bit_1);

	assert(g1_1_1.getState()			== one_bit_0);
	g1_1_1.tick();
	assert(g1_1_1.getState()			== one_bit_0);	// Output stayed 0 after tick()

	// NAND Gate with width 2 (2 inputs)
	assert(g2_0_0.getState()			== two_bit_0);
	g2_0_0.tick();
	assert(g2_0_0.getState()			== two_bit_3);

	assert(g2_0_1.getState()			== two_bit_0);
	g2_0_1.tick();
	assert(g2_0_1.getState()			== two_bit_3);

	assert(g2_1_0.getState()			== two_bit_0);
	g2_1_0.tick();
	assert(g2_1_0.getState()			== two_bit_3);

	assert(g2_1_1.getState()			== two_bit_0);
	g2_1_1.tick();
	assert(g2_1_1.getState()			== two_bit_2);	// Output stayed 0 after tick()

	assert(g2_0_2.getState()			== two_bit_0);
	g2_0_2.tick();
	assert(g2_0_2.getState()			== two_bit_3);

	assert(g2_1_2.getState()			== two_bit_0);
	g2_1_2.tick();
	assert(g2_1_2.getState()			== two_bit_3);

	assert(g2_0_3.getState()			== two_bit_0);
	g2_0_3.tick();
	assert(g2_0_3.getState()			== two_bit_3);

	assert(g2_1_3.getState()			== two_bit_0);
	g2_1_3.tick();
	assert(g2_1_3.getState()			== two_bit_2);	// Output stayed 0 after tick()
}

/*
 *	NAND Gate : Test dynamic logic.
 */
void testLogic_NAND_dynamic(void) {
	NANDGate<2> g2;

	g2.addInput( {&signal2_0, &signal2_0_} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_3);
	g2.removeInput(signal2_0);
	g2.removeInput(signal2_0_);
	assert(g2.getInputs().size()		== 0);

	g2.addInput( {&signal2_1, &signal2_2} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_3);
	g2.removeInput(signal2_2);
	assert(g2.getInputs().size()		== 1);

	g2.addInput(signal2_3);
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_2);
	g2.removeInput(signal2_1);
	g2.removeInput(signal2_3);
	assert(g2.getInputs().size()		== 0);
}

/*
 *	OR Gate : Test basic logic.
 */
void testLogic_OR_const(void) {
	ORGate<1>	g1_0_0(signalProvider1_0_0),
				g1_0_1(signalProvider1_0_1),
				g1_1_0(signalProvider1_1_0),
				g1_1_1(signalProvider1_1_1);
	ORGate<2>	g2_0_0(signalProvider2_0_0),
				g2_0_1(signalProvider2_0_1),
				g2_1_0(signalProvider2_1_0),
				g2_1_1(signalProvider2_1_1),
				g2_0_2(signalProvider2_0_2),
				g2_1_2(signalProvider2_1_2),
				g2_0_3(signalProvider2_0_3),
				g2_1_3(signalProvider2_1_3);

	// OR Gate with width 1 (2 inputs)
	assert(g1_0_0.getState()			== one_bit_0);
	g1_0_0.tick();
	assert(g1_0_0.getState()			== one_bit_0);

	assert(g1_0_1.getState()			== one_bit_0);
	g1_0_1.tick();
	assert(g1_0_1.getState()			== one_bit_1);

	assert(g1_1_0.getState()			== one_bit_0);
	g1_1_0.tick();
	assert(g1_1_0.getState()			== one_bit_1);

	assert(g1_1_1.getState()			== one_bit_0);
	g1_1_1.tick();
	assert(g1_1_1.getState()			== one_bit_1);	// Output changed to 1 after tick()

	// OR Gate with width 2 (2 inputs)
	assert(g2_0_0.getState()			== two_bit_0);
	g2_0_0.tick();
	assert(g2_0_0.getState()			== two_bit_0);

	assert(g2_0_1.getState()			== two_bit_0);
	g2_0_1.tick();
	assert(g2_0_1.getState()			== two_bit_1);

	assert(g2_1_0.getState()			== two_bit_0);
	g2_1_0.tick();
	assert(g2_1_0.getState()			== two_bit_1);

	assert(g2_1_1.getState()			== two_bit_0);
	g2_1_1.tick();
	assert(g2_1_1.getState()			== two_bit_1);	// Output changed to 1 after tick()

	assert(g2_0_2.getState()			== two_bit_0);
	g2_0_2.tick();
	assert(g2_0_2.getState()			== two_bit_2);

	assert(g2_1_2.getState()			== two_bit_0);
	g2_1_2.tick();
	assert(g2_1_2.getState()			== two_bit_3);

	assert(g2_0_3.getState()			== two_bit_0);
	g2_0_3.tick();
	assert(g2_0_3.getState()			== two_bit_3);

	assert(g2_1_3.getState()			== two_bit_0);
	g2_1_3.tick();
	assert(g2_1_3.getState()			== two_bit_3);	// Output changed to 1 after tick()
}

/*
 *	OR Gate : Test dynamic logic.
 */
void testLogic_OR_dynamic(void) {
	ORGate<2> g2;

	g2.addInput( {&signal2_0, &signal2_0_} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_0);
	g2.removeInput(signal2_0);
	g2.removeInput(signal2_0_);
	assert(g2.getInputs().size()		== 0);

	g2.addInput( {&signal2_1, &signal2_2} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_3);
	g2.removeInput(signal2_2);
	assert(g2.getInputs().size()		== 1);

	g2.addInput(signal2_3);
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_3);
	g2.removeInput(signal2_1);
	g2.removeInput(signal2_3);
	assert(g2.getInputs().size()		== 0);
}

/*
 *	NOR Gate : Test basic logic.
 */
void testLogic_NOR_const(void) {
	NORGate<1>	g1_0_0(signalProvider1_0_0),
				g1_0_1(signalProvider1_0_1),
				g1_1_0(signalProvider1_1_0),
				g1_1_1(signalProvider1_1_1);
	NORGate<2>	g2_0_0(signalProvider2_0_0),
				g2_0_1(signalProvider2_0_1),
				g2_1_0(signalProvider2_1_0),
				g2_1_1(signalProvider2_1_1),
				g2_0_2(signalProvider2_0_2),
				g2_1_2(signalProvider2_1_2),
				g2_0_3(signalProvider2_0_3),
				g2_1_3(signalProvider2_1_3);

	// NOR Gate with width 1 (2 inputs)
	assert(g1_0_0.getState()			== one_bit_0);
	g1_0_0.tick();
	assert(g1_0_0.getState()			== one_bit_1);

	assert(g1_0_1.getState()			== one_bit_0);
	g1_0_1.tick();
	assert(g1_0_1.getState()			== one_bit_0);

	assert(g1_1_0.getState()			== one_bit_0);
	g1_1_0.tick();
	assert(g1_1_0.getState()			== one_bit_0);

	assert(g1_1_1.getState()			== one_bit_0);
	g1_1_1.tick();
	assert(g1_1_1.getState()			== one_bit_0);	// Output changed to 1 after tick()

	// NOR Gate with width 2 (2 inputs)
	assert(g2_0_0.getState()			== two_bit_0);
	g2_0_0.tick();
	assert(g2_0_0.getState()			== two_bit_3);

	assert(g2_0_1.getState()			== two_bit_0);
	g2_0_1.tick();
	assert(g2_0_1.getState()			== two_bit_2);

	assert(g2_1_0.getState()			== two_bit_0);
	g2_1_0.tick();
	assert(g2_1_0.getState()			== two_bit_2);

	assert(g2_1_1.getState()			== two_bit_0);
	g2_1_1.tick();
	assert(g2_1_1.getState()			== two_bit_2);	// Output changed to 1 after tick()

	assert(g2_0_2.getState()			== two_bit_0);
	g2_0_2.tick();
	assert(g2_0_2.getState()			== two_bit_1);

	assert(g2_1_2.getState()			== two_bit_0);
	g2_1_2.tick();
	assert(g2_1_2.getState()			== two_bit_0);

	assert(g2_0_3.getState()			== two_bit_0);
	g2_0_3.tick();
	assert(g2_0_3.getState()			== two_bit_0);

	assert(g2_1_3.getState()			== two_bit_0);
	g2_1_3.tick();
	assert(g2_1_3.getState()			== two_bit_0);	// Output changed to 1 after tick()
}

/*
 *	NOR Gate : Test dynamic logic.
 */
void testLogic_NOR_dynamic(void) {
	NORGate<2> g2;

	g2.addInput( {&signal2_0, &signal2_0_} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_3);
	g2.removeInput(signal2_0);
	g2.removeInput(signal2_0_);
	assert(g2.getInputs().size()		== 0);

	g2.addInput( {&signal2_1, &signal2_2} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_0);
	g2.removeInput(signal2_2);
	assert(g2.getInputs().size()		== 1);

	g2.addInput(signal2_3);
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_0);
	g2.removeInput(signal2_1);
	g2.removeInput(signal2_3);
	assert(g2.getInputs().size()		== 0);
}

/*
 *	XOR Gate : Test basic logic.
 */
void testLogic_XOR_const(void) {
	XORGate<1>	g1_0_0(signalProvider1_0_0),
				g1_0_1(signalProvider1_0_1),
				g1_1_0(signalProvider1_1_0),
				g1_1_1(signalProvider1_1_1);
	XORGate<2>	g2_0_0(signalProvider2_0_0),
				g2_0_1(signalProvider2_0_1),
				g2_1_0(signalProvider2_1_0),
				g2_1_1(signalProvider2_1_1),
				g2_0_2(signalProvider2_0_2),
				g2_1_2(signalProvider2_1_2),
				g2_0_3(signalProvider2_0_3),
				g2_1_3(signalProvider2_1_3);

	// XOR Gate with width 1 (2 inputs)
	assert(g1_0_0.getState()			== one_bit_0);
	g1_0_0.tick();
	assert(g1_0_0.getState()			== one_bit_0);

	assert(g1_0_1.getState()			== one_bit_0);
	g1_0_1.tick();
	assert(g1_0_1.getState()			== one_bit_1);

	assert(g1_1_0.getState()			== one_bit_0);
	g1_1_0.tick();
	assert(g1_1_0.getState()			== one_bit_1);

	assert(g1_1_1.getState()			== one_bit_0);
	g1_1_1.tick();
	assert(g1_1_1.getState()			== one_bit_0);	// Output changed to 1 after tick()

	// XOR Gate with width 2 (2 inputs)
	assert(g2_0_0.getState()			== two_bit_0);
	g2_0_0.tick();
	assert(g2_0_0.getState()			== two_bit_0);

	assert(g2_0_1.getState()			== two_bit_0);
	g2_0_1.tick();
	assert(g2_0_1.getState()			== two_bit_1);

	assert(g2_1_0.getState()			== two_bit_0);
	g2_1_0.tick();
	assert(g2_1_0.getState()			== two_bit_1);

	assert(g2_1_1.getState()			== two_bit_0);
	g2_1_1.tick();
	assert(g2_1_1.getState()			== two_bit_0);	// Output changed to 1 after tick()

	assert(g2_0_2.getState()			== two_bit_0);
	g2_0_2.tick();
	assert(g2_0_2.getState()			== two_bit_2);

	assert(g2_1_2.getState()			== two_bit_0);
	g2_1_2.tick();
	assert(g2_1_2.getState()			== two_bit_3);

	assert(g2_0_3.getState()			== two_bit_0);
	g2_0_3.tick();
	assert(g2_0_3.getState()			== two_bit_3);

	assert(g2_1_3.getState()			== two_bit_0);
	g2_1_3.tick();
	assert(g2_1_3.getState()			== two_bit_2);	// Output changed to 1 after tick()

	g2_1_3.addInput(signal2_1_);	// Test case: 1^1^1 == 1
	assert(g2_1_3.getInputs().size()	== 3);
	g2_1_3.tick();
	assert(g2_1_3.getState()			== two_bit_3);	// 01^11^01 = 11
}

/*
 *	XOR Gate : Test dynamic logic.
 */
void testLogic_XOR_dynamic(void) {
	XORGate<2> g2;

	g2.addInput( {&signal2_0, &signal2_0_} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_0);
	g2.removeInput(signal2_0);
	g2.removeInput(signal2_0_);
	assert(g2.getInputs().size()		== 0);

	g2.addInput( {&signal2_1, &signal2_2} );
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_3);
	g2.removeInput(signal2_2);
	assert(g2.getInputs().size()		== 1);

	g2.addInput(signal2_3);
	assert(g2.getInputs().size()		== 2);
	g2.tick();
	assert(g2.getState()				== two_bit_2);
	g2.removeInput(signal2_1);
	g2.removeInput(signal2_3);
	assert(g2.getInputs().size()		== 0);
}

/*
 *	NOT Gate : Test basic logic.
 */
void testLogic_NOT_const(void) {
	NOTGate<1>	g1_0( { &signal1_0 } ),	// equivalent to g1_0; g1_0.addInput(signal1_0);
				g1_1( { &signal1_1 } );
	NOTGate<2>	g2_0( { &signal2_0 } ),
				g2_1( { &signal2_1 } ),
				g2_2( { &signal2_2 } ),
				g2_3( { &signal2_3 } );

	// NOT Gate with width 1 (1 input)
	assert(g1_0.getState()				== one_bit_0);
	g1_0.tick();
	assert(g1_0.getState()				== one_bit_1);	// Output changed to 1 after tick()

	assert(g1_1.getState()				== one_bit_0);
	g1_1.tick();
	assert(g1_1.getState()				== one_bit_0);

	// NOT Gate with width 2 (1 input)
	assert(g2_0.getState()				== two_bit_0);
	g2_0.tick();
	assert(g2_0.getState()				== two_bit_3);

	assert(g2_1.getState()				== two_bit_0);
	g2_1.tick();
	assert(g2_1.getState()				== two_bit_2);

	assert(g2_2.getState()				== two_bit_0);
	g2_2.tick();
	assert(g2_2.getState()				== two_bit_1);

	assert(g2_3.getState()				== two_bit_0);
	g2_3.tick();
	assert(g2_3.getState()				== two_bit_0);
}

/*
 *	NOT Gate : Test dynamic logic.
 */
void testLogic_NOT_dynamic(void) {
	NOTGate<2> g2;

	g2.addInput(signal2_0);
	assert(g2.getInputs().size()		== 1);
	g2.tick();
	assert(g2.getState()				== two_bit_3);
	g2.removeInput(signal2_0);
	assert(g2.getInputs().size()		== 0);

	g2.addInput(signal2_1);
	assert(g2.getInputs().size()		== 1);
	g2.tick();
	assert(g2.getState()				== two_bit_2);
	g2.removeInput(signal2_1);
	assert(g2.getInputs().size()		== 0);

	g2.addInput(signal2_3);
	assert(g2.getInputs().size()		== 1);
	g2.tick();
	assert(g2.getState()				== two_bit_0);
	g2.removeInput(signal2_3);
	assert(g2.getInputs().size()		== 0);
}

/*
 *	All gates : Test logic combinations.
 */
void testLogic_Combinations(void) {
	// TO-DO

	// NOT(AND(x, y)) == NAND(x, y)
	ANDGate<2>	and_2(signalProvider2_1_3);
	NOTGate<2>	not_and_1( { &and_2 } );
	NANDGate<2>	nand_2(signalProvider2_1_3);

	// NOT(OR(x, y)) == NOR(x, y)
	ORGate<2>	or_2(signalProvider2_1_3);
	NOTGate<2>	not_or_1( { &or_2 } );
	NORGate<2>	nor_2(signalProvider2_1_3);

	assert(and_2.getInputs().size()		== 2);
	assert(and_2.getOutputs().size()	== 1);
	assert(not_and_1.getInputs().size()	== 1);
	assert(not_and_1.getOutputs().size()== 0);
	assert(nand_2.getInputs().size()	== 2);
	assert(nand_2.getOutputs().size()	== 0);

	assert(or_2.getInputs().size()		== 2);
	assert(or_2.getOutputs().size()		== 1);
	assert(not_or_1.getInputs().size()	== 1);
	assert(not_or_1.getOutputs().size()	== 0);
	assert(nor_2.getInputs().size()		== 2);
	assert(nor_2.getOutputs().size()	== 0);

	signal2_1.emit();
	// Has signalProvider2_1_3 as Slot, will cause emit() chain:
	// signal2_1 -> signalProvider2_1_3.tick()
	// { signal2_1, signal2_3 } -> signalProvider2_1_3.emit()
	// signalProvider2_1_3 -> { and_2, nand_2, or_2, nor_2 }.tick() ...
	assert(not_and_1.getState()			== nand_2.getState());
	assert(not_or_1.getState()			== nor_2.getState());
}

void testLogic_MemoryCell(void) {
	SynchrotronComponent<1> signal_i(one_bit_0.to_ulong()),
							signal_s(one_bit_1.to_ulong());
	NANDGate<1>				nand_1( {&signal_i, &signal_s} ),
							nand_2( {&nand_1, &signal_s} ),
							nand_3(one_bit_1.to_ulong()),
							nand_4(one_bit_1.to_ulong());
							nand_3.addInput( {&nand_1, &nand_4} );
							nand_4.addInput( {&nand_2, &nand_3} );

	std::cout << "States: " << nand_1.getState() << ", "
							<< nand_2.getState() << ", "
							<< nand_3.getState() << ", "
							<< nand_4.getState() << ", "
							<< "Mem bit: " << nand_3.getState() << std::endl;
	signal_i.emit();
	std::cout << "States: " << nand_1.getState() << ", "
							<< nand_2.getState() << ", "
							<< nand_3.getState() << ", "
							<< nand_4.getState() << ", "
							<< "Mem bit: " << nand_3.getState() << std::endl;

	MemoryCell<1> m({&nand_1});
	std::cout << " State: " << nand_1.getState() << " :: " << &nand_1 << std::endl;

	std::cout << "Memory: " << m.getInput().getState() << " :: " << &m.getInput() << std::endl;
}

void testLogic_ShiftRight_const(void) {
	SHIFTRight<1>	g1_0( { &signal1_0 } ),	// equivalent to g1_0; g1_0.addInput(signal1_0);
					g1_1( { &signal1_1 } );
	SHIFTRight<2>	g2_0( { &signal2_0 } ),
					g2_1( { &signal2_1 } ),
					g2_2( { &signal2_2 } ),
					g2_3( { &signal2_3 } );
	SHIFTRight<4>	g4_8( { &signal4_8 } ),	// 1000
					g4_A( { &signal4_A } );	// 1010

	assert(g1_0.getInputs().size()		== 1);
	assert(g1_0.getState()				== one_bit_0);
	g1_0.tick();
	assert(g1_0.getState()				== one_bit_0);	//  0 >> 1 ==  0

	assert(g1_1.getInputs().size()		== 1);
	assert(g1_1.getState()				== one_bit_0);
	g1_1.tick();
	assert(g1_1.getState()				== one_bit_0);	//  1 >> 1 ==  0

	assert(g2_0.getState()				== two_bit_0);
	g2_0.tick();
	assert(g2_0.getState()				== two_bit_0);	// 00 >> 1 == 00

	assert(g2_1.getState()				== two_bit_0);
	g2_1.tick();
	assert(g2_1.getState()				== two_bit_0);	// 01 >> 1 == 00

	assert(g2_2.getState()				== two_bit_0);
	g2_2.tick();
	assert(g2_2.getState()				== two_bit_1);	// 10 >> 1 == 01

	assert(g2_3.getState()				== two_bit_0);
	g2_3.tick();
	assert(g2_3.getState()				== two_bit_1);	// 11 >> 1 == 01

	assert(g4_8.getInputs().size()		== 1);
	assert(g4_A.getInputs().size()		== 1);

	assert(g4_8.getState()				== for_bit_0);
	g4_8.tick();
	assert(g4_8.getState()				== for_bit_4);	// 1000 >> 1 == 0100
	g4_8.tick();
	assert(g4_8.getState()				== for_bit_4);	// No change : input is still 0x8

	assert(g4_A.getState()				== for_bit_0);
	g4_A.tick();
	assert(g4_A.getState()				== for_bit_5);	// 1010 >> 1 == 0101
	g4_A.tick();
	assert(g4_A.getState()				== for_bit_5);	// No change : input is still 0xA
}

void testLogic_ShiftRight_dynamic(void) {
	SHIFTRight<4>	gCycle( signal4_A.getState().to_ulong() );

	// Create emit loop : will shift value continiously until all zero
	// Note: This has been verified to operate correctly.
	gCycle.addInput(gCycle);
	assert(gCycle.getState()			== for_bit_A);
	gCycle.tick();	// Start emit chain
	assert(gCycle.getState()			== for_bit_0);
}

void testLogic_ShiftLeft_const(void) {
	SHIFTLeft<1>	g1_0( { &signal1_0 } ),	// equivalent to g1_0; g1_0.addInput(signal1_0);
					g1_1( { &signal1_1 } );
	SHIFTLeft<2>	g2_0( { &signal2_0 } ),
					g2_1( { &signal2_1 } ),
					g2_2( { &signal2_2 } ),
					g2_3( { &signal2_3 } );
	SHIFTLeft<4>	g4_8( { &signal4_8 } ),	// 1000
					g4_A( { &signal4_A } );	// 1010

	assert(g1_0.getInputs().size()		== 1);
	assert(g1_0.getState()				== one_bit_0);
	g1_0.tick();
	assert(g1_0.getState()				== one_bit_0);	//  0 << 1 ==  0

	assert(g1_1.getInputs().size()		== 1);
	assert(g1_1.getState()				== one_bit_0);
	g1_1.tick();
	assert(g1_1.getState()				== one_bit_0);	//  1 << 1 ==  0

	assert(g2_0.getState()				== two_bit_0);
	g2_0.tick();
	assert(g2_0.getState()				== two_bit_0);	// 00 << 1 == 00

	assert(g2_1.getState()				== two_bit_0);
	g2_1.tick();
	assert(g2_1.getState()				== two_bit_2);	// 01 << 1 == 10

	assert(g2_2.getState()				== two_bit_0);
	g2_2.tick();
	assert(g2_2.getState()				== two_bit_0);	// 10 << 1 == 00

	assert(g2_3.getState()				== two_bit_0);
	g2_3.tick();
	assert(g2_3.getState()				== two_bit_2);	// 11 << 1 == 10

	assert(g4_8.getInputs().size()		== 1);
	assert(g4_A.getInputs().size()		== 1);

	assert(g4_8.getState()				== for_bit_0);
	g4_8.tick();
	assert(g4_8.getState()				== for_bit_0);	// 1000 << 1 == 0000
	g4_8.tick();
	assert(g4_8.getState()				== for_bit_0);	// No change : input is still 0x8

	assert(g4_A.getState()				== for_bit_0);
	g4_A.tick();
	assert(g4_A.getState()				== for_bit_4);	// 1010 << 1 == 0100
	g4_A.tick();
	assert(g4_A.getState()				== for_bit_4);	// No change : input is still 0xA
}

void testLogic_ShiftLeft_dynamic(void) {
	SHIFTLeft<4>	gCycle( signal4_A.getState().to_ulong() );

	// Create emit loop : will shift value continiously until all zero
	// Note: This has been verified to operate correctly.
	gCycle.addInput(gCycle);
	assert(gCycle.getState()			== for_bit_A);
	gCycle.tick();	// Start emit chain
	assert(gCycle.getState()			== for_bit_0);
}

void testLogic_Memory(void) {
	int i;
	Memory<2, 1>	m_2_1(MemoryUnits::BITS);
	Memory<4, 8>	m_4_8(MemoryUnits::BYTES);
	std::bitset<4> *range;

	assert(m_2_1.getSize()				== 2);
	assert(m_2_1.getSizeUnit()			== MemoryUnits::BITS);
	assert(m_2_1.getMaxSize()			== 3);
	assert(m_2_1.getMaxAddress()		== two_bit_0);
	assert(m_2_1.getData(two_bit_0)		== two_bit_0);
	m_2_1.setData(two_bit_0, two_bit_1);
	assert(m_2_1.getData(two_bit_0)		== two_bit_1);
	m_2_1.setData(two_bit_0, two_bit_3);
	assert(m_2_1.getData(two_bit_0)		== two_bit_3);
	m_2_1.resetData(two_bit_0);
	assert(m_2_1.getData(two_bit_0)		== two_bit_0);


	assert(m_4_8.getSize()				== 4);
	assert(m_4_8.getSizeUnit()			== MemoryUnits::BYTES);
	assert(m_4_8.getMaxSize()			== 15);
	assert(m_4_8.getMaxAddress()		== for_bit_7);
	assert(m_4_8.getData(for_bit_0)		== for_bit_0);
	m_4_8.setData(for_bit_0, for_bit_1);
	assert(m_4_8.getData(for_bit_0)		== for_bit_1);
	m_4_8.setData(for_bit_7, for_bit_5);
	assert(m_4_8.getData(for_bit_7)		== for_bit_5);
	m_4_8.resetData(for_bit_7);
	assert(m_4_8.getData(for_bit_7)		== for_bit_0);
	m_4_8.setData(for_bit_7, for_bit_7);
	assert(m_4_8.getData(for_bit_7)		== for_bit_7);

	range = m_4_8.getDataRange(for_bit_0, for_bit_7);
	for (i = 0; i < 8; ++i)
		assert(range[i]					== (!i ? for_bit_1 : i == 7 ? for_bit_7 : for_bit_0));
//	delete range;	// Invalid vor MSVC?

	range = m_4_8.getDataRange(for_bit_7, for_bit_7);
	assert(range[0]						== for_bit_7);
//	delete range;	// Invalid vor MSVC?
}

void testClock(void) {
	Clock<1u> c(1.0F);

	assert(c.getBitWidth()				== 1);
	assert(c.getFrequency()				== 1.0F);
	assert(c.getPeriod()				== 1.0F);

	c.setFrequency(4.0);
	assert(c.getFrequency()				== 4.0F);
	assert(c.getPeriod()				== 0.25F);

	c.setPeriod(0.5);
	assert(c.getFrequency()				== 2.0F);
	assert(c.getPeriod()				== 0.5F);

	//assert(c.startThread()				== true);

	// TO-DO: Test emit cycle
}

/*
 *	Run all tests.
 */
void runTests(void) {
	int errorlevel = 0;

	try {
		testBitset();
		testSynchrotronComponent();
		testLogic_AND_const();
		testLogic_AND_dynamic();
		testLogic_NAND_const();
		testLogic_NAND_dynamic();
		testLogic_OR_const();
		testLogic_OR_dynamic();
		testLogic_NOR_const();
		testLogic_NOR_dynamic();
		testLogic_XOR_const();
		testLogic_XOR_dynamic();
		testLogic_NOT_const();
		testLogic_NOT_dynamic();
		testLogic_Combinations();
		testLogic_MemoryCell();			// WIP
		testLogic_ShiftRight_const();
		testLogic_ShiftRight_dynamic();
		testLogic_ShiftLeft_const();
		testLogic_ShiftLeft_dynamic();
		testLogic_Memory();
		testClock();					// WIP
	} catch (Exceptions::Exception const& e) {
		std::cerr << e.getMessage() << std::endl;
		errorlevel++;
	} catch(...) {
		std::cerr << "Unknown exception." << std::endl;
		errorlevel++;
	}

	std::cout << (errorlevel ? "There were errors running tests. See message(s) above." :
							   "All tests passed.") << std::endl;
}


#endif // ifndef NDEBUG

#endif // UNITTEST_HPP
