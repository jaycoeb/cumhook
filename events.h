#pragma once

class Listener : public IGameEventListener2 {
	using game_event_t = void( __cdecl* )( IGameEvent* );

private:
	std::map< std::string, std::vector< game_event_t > > m_events;

public:
	// ctor.
	__forceinline Listener( ) : m_events{} {
		m_debug_id = 42;
	}

	void init( );

	__forceinline void add( const std::string& name, game_event_t fn ) {
		m_events[ name ].push_back( fn );
	}

	__forceinline void register_events( ) {
		if( m_events.empty( ) )
			return;

		for( const auto& e : m_events )
			g_csgo.m_game_events->AddListener( this, e.first.data( ), false );
	}

	//__forceinline void unregister_events( ) {
	//	g_csgo.m_game_events->RemoveListener( this );
	//}

	void FireGameEvent( IGameEvent* evt ) override {
		const std::string name = evt->GetName( );

		if( m_events.count( name ) != 0 ) {
			const auto& events = m_events[ name ];
			for( const auto& e : events )
				e( evt );
		}
	}
};

namespace events {
	void round_start( IGameEvent* evt );
	void round_end( IGameEvent* evt );
	void player_hurt( IGameEvent* evt );
	void on_fire(IGameEvent* evt);
	void bullet_impact( IGameEvent* evt );
	void item_purchase( IGameEvent* evt );
	void player_death( IGameEvent* evt );
	void player_given_c4( IGameEvent* evt );
	void bomb_beginplant( IGameEvent* evt );
	void bomb_abortplant( IGameEvent* evt );
	void bomb_planted( IGameEvent* evt );
    void bomb_beep( IGameEvent* evt );
	void bomb_begindefuse( IGameEvent* evt );
	void bomb_abortdefuse( IGameEvent* evt );
    void bomb_defused( IGameEvent* evt );
    void bomb_exploded( IGameEvent* evt );
	void player_footstep(IGameEvent* evt);

}
class CSoundEsp {
public:
	void DrawSteps();
	void ClearSteps();
	void AddStepManually(int ent, vec3_t origin);

public:
	class CSoundEsp_info {
	public:
		CSoundEsp_info(vec3_t origin, float time, Color color) {
			this->origin = origin;
			this->time = time;
			this->color = color;
		}

		vec3_t origin;
		float time;
		Color color;
		Beam_t* beamInfo;
	};

	std::vector<CSoundEsp_info> StepsData;
};

extern CSoundEsp SoundEsp;
extern Listener g_listener;