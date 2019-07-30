import React, {PureComponent} from 'react';
import Card from 'react-bootstrap/Card';
import Col from 'react-bootstrap/Col';
import PropTypes from 'prop-types';
import Row from 'react-bootstrap/Row';
import pc from './parameters';

class Limiter extends PureComponent {
  render() {
    const {
      channelName,
      limiter,
      limiterThreshold,
      limiterRelease,
      channelId,
      onChange,
      group
    } = this.props;

    return (
      <Card>
        <Card.Header>
          {channelName
            ? `${channelId} . ${channelName}`
            : `Channel ${channelId}`}
        </Card.Header>
        <Card.Body>
          <Row>
            <Col xs={6} md={12} lg={6}>
              <pc.Limiter
                includeLabel
                value={limiter}
                group={group}
                channelId={channelId}
                onChange={onChange}
              />
            </Col>
            <Col xs={6} md={12} lg={6}>
              <pc.LimiterRelease
                includeLabel
                value={limiterRelease}
                group={group}
                channelId={channelId}
                onChange={onChange}
              />
            </Col>
          </Row>
          <pc.LimiterThreshold
            includeLabel
            value={limiterThreshold}
            group={group}
            channelId={channelId}
            onChange={onChange}
          />
        </Card.Body>
      </Card>
    );
  }
}

Limiter.propTypes = {
  channelId: PropTypes.string.isRequired,
  group: PropTypes.string.isRequired,
  channelName: PropTypes.string.isRequired,
  limiter: PropTypes.bool.isRequired,
  limiterThreshold: PropTypes.number.isRequired,
  limiterRelease: PropTypes.string.isRequired,
  onChange: PropTypes.func.isRequired
};

export default Limiter;
