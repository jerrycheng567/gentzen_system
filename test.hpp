#ifndef THEOREM_PROVER_EXAMPLE
#define THEOREM_PROVER_EXAMPLE
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "first_order_logic.hpp"
//#include "praser.hpp"
#include "gentzen_system.hpp"
#include "substitution.hpp"
#include "definite_clause.hpp"
#include "knowledge_base.hpp"
namespace first_order_logic
{
	BOOST_AUTO_TEST_CASE( gentzen_system_test )
	{
		auto fol = make_imply(
								 make_all( "x", make_predicate( "F", { make_variable( "x" ) } ) ),
								 make_all( "x", make_predicate( "F", { make_function( "f", { make_variable( "x" ) } ) } ) ) );
		auto fol2 = make_imply(
									make_some
									(
										"x",
										make_imply
										(
											make_propositional_letter( "p" ),
											make_predicate( "Q", { make_variable( "x" ) } )
										)
									),
									make_imply
									(
										make_propositional_letter( "p" ),
										make_some
										(
											"z",
											make_predicate( "Q", { make_variable( "z" ) } )
										)
									)
								);
		auto fol3 =
				make_imply
				(
					make_and
					(
						make_all
						(
							"x",
							make_predicate( "P", { make_variable( "x" ) } )
						),
						make_some( "y", make_predicate( "Q", { make_variable( "y" ) } ) )
					),
					make_and
					(
						make_predicate
						(
							"P",
							{ make_function( "F",  { make_variable( "v" ) } ) }
						),
						make_some( "z", make_predicate( "Q", { make_variable( "z" ) } ) )
					)
				);
		auto fol4 =
				make_imply
				(
					make_and
					(
						make_predicate( "p", { make_variable( "x" ) } ),
						make_equal( make_function( "f", { make_variable( "x" ) } ), make_variable( "x" ) )
					),
					make_predicate( "p", { make_function( "f", { make_variable( "x" ) } ) } )
				);

		BOOST_CHECK( gentzen_system::is_valid( fol ).second );
		BOOST_CHECK( gentzen_system::is_valid( fol2 ).second );
		BOOST_CHECK( gentzen_system::is_valid( fol3 ).second );
		BOOST_CHECK( gentzen_system::is_valid( fol4 ).second );
	}
	BOOST_AUTO_TEST_CASE( forward_chaning_algorithm )
	{
		knowledge_base kb;
		kb.kb.push_back( definite_clause(
			{ make_predicate( "Missile", { make_variable( "x" ) } ) },
			make_predicate( "Weapon", { make_variable( "x" ) } ) ) );
		kb.kb.push_back( definite_clause(
			{
				make_predicate( "American", { make_variable( "x" ) } ),
				make_predicate( "Weapon", { make_variable( "y" ) } ),
				make_predicate( "Sell", { make_variable( "x" ), make_variable( "y" ), make_variable( "z" ) } ),
				make_predicate( "Hostile", { make_variable( "z" ) } )
			},
			make_predicate( "Criminal", { make_variable( "x" ) } ) ) );
		kb.kb.push_back( definite_clause(
			{
				make_predicate( "Missile", { make_variable( "x" ) } ),
				make_predicate( "Owns", { make_constant( "Nono" ), make_variable( "x" ) } )
			},
			make_predicate( "Sell", { make_constant( "West" ), make_variable( "x" ), make_constant( "Nono" ) } ) ) );
		kb.kb.push_back( definite_clause(
			{ make_predicate( "Enemy", { make_variable( "x" ), make_constant( "America" ) } ) },
			make_predicate( "Hostile", { make_variable( "x" ) } ) ) );
		kb.known_facts.push_back( make_predicate( "Owns", { make_constant( "Nono" ), make_constant( "M1" ) } ) );
		kb.known_facts.push_back( make_predicate( "Missile", { make_constant( "M1" ) } ) );
		kb.known_facts.push_back( make_predicate( "American", { make_constant( "West" ) } ) );
		kb.known_facts.push_back( make_predicate( "Enemy", { make_constant( "Nono" ), make_constant( "America" ) } ) );
		BOOST_CHECK( kb.forward_chaining( make_predicate( "Criminal", { make_variable( "x" ) } ) ) );
	}
}
#endif //THEOREM_PROVER_EXAMPLE
