#pragma once

#include <base/info/media_track.h>
#include <base/publisher/session.h>
#include <modules/mpegts/mpegts_writer.h>
#include "base/info/push.h"

class MpegtsPushSession : public pub::Session
{
public:
	static std::shared_ptr<MpegtsPushSession> Create(const std::shared_ptr<pub::Application> &application,
											  const std::shared_ptr<pub::Stream> &stream,
											  uint32_t ovt_session_id,
											  std::shared_ptr<info::Push> &push);

	MpegtsPushSession(const info::Session &session_info,
			const std::shared_ptr<pub::Application> &application,
			const std::shared_ptr<pub::Stream> &stream,
			const std::shared_ptr<info::Push> &push);
	~MpegtsPushSession() override;

	bool Start() override;
	bool Stop() override;

	void SendOutgoingData(const std::any &packet) override;
	
	void SetPush(std::shared_ptr<info::Push> &record);
	std::shared_ptr<info::Push>& GetPush();
	
private:
	std::shared_ptr<info::Push> _push;
	
	std::shared_mutex _mutex;
	
	std::shared_ptr<MpegtsWriter> _writer;
};
